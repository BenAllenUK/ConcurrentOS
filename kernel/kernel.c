#include "kernel.h"

pcb_t pcb[ MAX_PROCCESORS ], *current = NULL;
queue_t pcb_queue;
queue_t input_request_queue;
queue_t user_input_queue;

int time_slices_left = 0;

void scheduler( ctx_t* ctx ) {
  if(time_slices_left == 0) {
    // Switch process
    int current_pid = pcb[ fifo_peek(&pcb_queue) ].pid;

    // Save and then add back to queue at the end
    memcpy( &pcb[ fifo_pop(&pcb_queue) ].ctx, ctx, sizeof( ctx_t ) );
    fifo_push(&pcb_queue, current_pid);

    // Copy in the new proccesor
    memcpy( ctx, &pcb[ fifo_peek(&pcb_queue) ].ctx, sizeof( ctx_t ) );

    time_slices_left = pcb[ fifo_peek(&pcb_queue) ].stats.priority;
  } else {
    // Continue with current process
    time_slices_left--;
  }
}

void kernel_handler_rst( ctx_t* ctx              ) {
  /* Initialise PCBs representing processes stemming from execution of
   * the two user programs.  Note in each case that
   *
   * - the CPSR value of 0x50 means the processor is switched into USR
   *   mode, with IRQ interrupts enabled, and
   * - the PC and SP values matche the entry point and top of stack.
   */

  fifo_init(&pcb_queue);
  fifo_init(&input_request_queue);
  fifo_init(&user_input_queue);

  memset( &pcb[ 0 ], 0, sizeof( pcb_t ) );
  pcb[ 0 ].pid      = 0;
  pcb[ 0 ].ctx.cpsr = 0x50;
  pcb[ 0 ].ctx.pc   = ( uint32_t )( entry_PDef );
  pcb[ 0 ].ctx.sp   = ( uint32_t )(  &tos_PDef );
  pcb[ 0 ].stats.priority = 1;
  pcb[ 0 ].stats.parentId = 0;
  fifo_push(&pcb_queue, 0);

  memset( &pcb[ 1 ], 0, sizeof( pcb_t ) );
  pcb[ 1 ].pid      = 1;
  pcb[ 1 ].ctx.cpsr = 0x50;
  pcb[ 1 ].ctx.pc   = ( uint32_t )( entry_P0 );
  pcb[ 1 ].ctx.sp   = ( uint32_t )(  &tos_P0 );
  pcb[ 1 ].stats.priority = 1;
  pcb[ 1 ].stats.parentId = 0;
  // fifo_push(&pcb_queue, 1);

  memset( &pcb[ 2 ], 0, sizeof( pcb_t ) );
  pcb[ 2 ].pid      = 2;
  pcb[ 2 ].ctx.cpsr = 0x50;
  pcb[ 2 ].ctx.pc   = ( uint32_t )( entry_P1 );
  pcb[ 2 ].ctx.sp   = ( uint32_t )(  &tos_P1 );
  pcb[ 2 ].stats.priority = 1;
  pcb[ 2 ].stats.parentId = 0;
  // fifo_push(&pcb_queue, 2);

  memset( &pcb[ 3 ], 0, sizeof( pcb_t ) );
  pcb[ 3 ].pid      = 3;
  pcb[ 3 ].ctx.cpsr = 0x50;
  pcb[ 3 ].ctx.pc   = ( uint32_t )( entry_P2 );
  pcb[ 3 ].ctx.sp   = ( uint32_t )(  &tos_P2 );
  pcb[ 3 ].stats.priority = 1;
  pcb[ 3 ].stats.parentId = 0;
  // fifo_push(&pcb_queue, 3);

  /* Once the PCBs are initialised, we (arbitrarily) select one to be
   * restored (i.e., executed) when the function then returns.
   */

  memcpy( ctx, &pcb[ fifo_peek(&pcb_queue) ].ctx, sizeof( ctx_t ) );
  time_slices_left = pcb[ fifo_pop(&pcb_queue) ].stats.priority;

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
    fifo_push(&user_input_queue, x);
    PL011_putc( UART0, x );

    UART0->ICR = 0x10;
  } else {
    PL011_putc( UART0, '\n' );
  }

  // Step 5: write the interrupt identifier to signal we're done.

  GICC0->EOIR = id;
}
