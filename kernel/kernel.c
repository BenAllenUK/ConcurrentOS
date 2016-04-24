#include "kernel.h"

pcb_t pcb[ MAX_PROCCESORS ], *current = NULL;
queue_t pcb_queue;
queue_t input_request_queue;
queue_t user_input_queue;
int current_focus = 0;

void scheduler( ctx_t* ctx ) {
  if(core_process_finished()) {
    core_save(&pcb_queue,  pcb, ctx);
    // Copy in the new proccesor
    core_new(&pcb_queue,  pcb, ctx);
  } else {
    // Continue with current process
    core_decrease_time();
  }
}

void kernel_handler_rst( ctx_t* ctx              ) {


  fifo_init(&pcb_queue);
  fifo_init(&input_request_queue);
  fifo_init(&user_input_queue);

  ipc_init(2,3);
  top_of_stack = (uint32_t) &tos_All;
  // memset( &pcb[ 1 ], 0, sizeof( pcb_t ) );
  // pcb[ 1 ].pid      = 1;
  // pcb[ 1 ].ctx.cpsr = 0x50;
  // pcb[ 1 ].ctx.pc   = ( uint32_t )( entry_PDef );
  // pcb[ 1 ].ctx.sp   = ( uint32_t )(  &tos_PDef );
  // pcb[ 1 ].stats.priority = 1;
  // pcb[ 1 ].stats.parentId = 1;
  // fifo_push(&pcb_queue, 1);
  // current_focus = 1;

  // memset( &pcb[ 1 ], 0, sizeof( pcb_t ) );
  // pcb[ 1 ].pid      = 1;
  // pcb[ 1 ].ctx.cpsr = 0x50;
  // pcb[ 1 ].ctx.pc   = ( uint32_t )( entry_P0 );
  // pcb[ 1 ].ctx.sp   = ( uint32_t )(  &tos_P0 );
  // pcb[ 1 ].stats.priority = 1;
  // pcb[ 1 ].stats.parentId = 0;
  // fifo_push(&pcb_queue, 1);

  memset( &pcb[ 2 ], 0, sizeof( pcb_t ) );
  pcb[ 2 ].pid      = 2;
  pcb[ 2 ].ctx.cpsr = 0x50;
  pcb[ 2 ].ctx.pc   = ( uint32_t )( entry_P1 );
  pcb[ 2 ].ctx.sp   = ( uint32_t )(  &tos_P1 );
  pcb[ 2 ].stats.priority = 5;
  pcb[ 2 ].stats.parentId = 0;
  fifo_push(&pcb_queue, 2);
  //
  memset( &pcb[ 3 ], 0, sizeof( pcb_t ) );
  pcb[ 3 ].pid      = 3;
  pcb[ 3 ].ctx.cpsr = 0x50;
  pcb[ 3 ].ctx.pc   = ( uint32_t )( entry_P2 );
  pcb[ 3 ].ctx.sp   = ( uint32_t )(  &tos_P2 );
  pcb[ 3 ].stats.priority = 10;
  pcb[ 3 ].stats.parentId = 0;
  fifo_push(&pcb_queue, 3);

  /* Once the PCBs are initialised, we (arbitrarily) select one to be
   * restored (i.e., executed) when the function then returns.
   */

  core_new(&pcb_queue,  pcb, ctx);

  TIMER0->Timer1Load     = TIMER_INTERVAL; // select period = 2^20 ticks ~= 1 sec
  TIMER0->Timer1Ctrl     = 0x00000002; // select 32-bit   timer
  TIMER0->Timer1Ctrl    |= 0x00000040; // select periodic timer
  TIMER0->Timer1Ctrl    |= 0x00000020; // enable          timer interrupt
  TIMER0->Timer1Ctrl    |= 0x00000080; // enable          timer

  GICC0->PMR             = 0x000000F0; // unmask all            interrupts
  GICD0->ISENABLER[ 1 ] |= 0x00001010; // enable timer          interrupt
  GICC0->CTLR            = 0x00000001; // enable GIC interface
  GICD0->CTLR            = 0x00000001; // enable GIC distributor

  UART0->IMSC           |= 0x00000010; // enable UART    (Rx) interrupt
  UART0->CR              = 0x00000301; // enable UART (Tx+Rx)

  irq_enable();


  system_init();

  return;
}



void kernel_handler_svc( ctx_t* ctx, uint32_t id ) {
  /* Based on the identified encoded as an immediate operand in the
   * instruction,
   *
   * - read  the arguments from preserved usr mode registers,
   * - perform whatever is appropriate for this system call,
   * - write any return value back to preserved usr mode registers.
   */

  switch( id ) {
    case 0x00 : { // yield()
      scheduler( ctx );
      break;
    }
    case 0x01 : { // write( fd, x, n )
      int   fd = ( int   )( ctx->gpr[ 0 ] );
      char*  x = ( char* )( ctx->gpr[ 1 ] );
      int    n = ( int   )( ctx->gpr[ 2 ] );

      for( int i = 0; i < n; i++ ) {
        PL011_putc( UART0, *x++ );
      }

      ctx->gpr[ 0 ] = n;
      break;
    }
    case 0x02 : { // read request
      int current_pid = pcb[ fifo_peek(&pcb_queue) ].pid;
      fifo_push(&input_request_queue, current_pid);
      break;
    }
    case 0x03 : { // read check for response
      int queueSize = fifo_size(&user_input_queue);

      if (queueSize > 0) {
        int char_entered = fifo_pop(&user_input_queue);
        ctx->gpr[ 0 ] = char_entered;
      } else {
        ctx->gpr[ 0 ] = '0';
      }
      break;
    }

    case 0x04: { // Get channel between here and x
      int to_pid = (int)(ctx->gpr[ 0 ]);
      int current_pid = pcb[ fifo_peek(&pcb_queue) ].pid;
      int chan_id = ipc_get_channel_id(to_pid, current_pid);
      if(chan_id != -1){
        ctx->gpr[ 0 ] = chan_id;
      }
      break;
    }

    case 0x05 : { // Fork
      core_save(&pcb_queue,  pcb, ctx);
      // core_fork(&pcb_queue, pcb, current_focus);
      break;
    }
    case 0x06: { // Exit
      core_save(&pcb_queue, pcb, ctx);
      core_exit(&pcb_queue, pcb, current_focus);
      current_focus = 0;
      break;
    }
    case 0x0A: { // Push
      int chan_id = (int)(ctx->gpr[ 0 ]);
      int to_id = (int)(ctx->gpr[ 1 ]);
      int data = (int)(ctx->gpr[ 2 ]);
      ipc_push(chan_id, to_id, data);

      break;
    }
    case 0x0B: { // Pull
        int chan_id = (int)(ctx->gpr[ 0 ]);
        int to_id = (int)(ctx->gpr[ 1 ]);
        int response = ipc_pull(chan_id, to_id);
        ctx->gpr[ 0 ] = response;
      break;
    }
    default   : { // unknown
      break;
    }
  }

  return;
}
void kernel_handler_irq(ctx_t* ctx, uint32_t id_s) {
  // Step 2: read  the interrupt identifier so we know the source.

  uint32_t id = GICC0->IAR;

  // Step 4: handle the interrupt, then clear (or reset) the source.

  if( id == GIC_SOURCE_TIMER0 ) {
    scheduler( ctx );
    TIMER0->Timer1IntClr = 0x01;
  } else if( id == GIC_SOURCE_UART0 ) {
    uint8_t x = PL011_getc( UART0 );
    if (x == ENTRY_CHAR){
      hide_display();
      current_focus = pcb[ fifo_peek(&pcb_queue) ].pid;
      write_str_raw("Enter Command: ");
    } else if (x == EXIT_CHAR){
      show_display();
    } else if(current_focus != 0) {
      fifo_push(&user_input_queue, x);
      PL011_putc( UART0, x );
    }

    UART0->ICR = 0x10;
  } else {
    PL011_putc( UART0, '\n' );
  }

  // Step 5: write the interrupt identifier to signal we're done.

  GICC0->EOIR = id;
}
