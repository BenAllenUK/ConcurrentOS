#include "kernel.h"

pcb_t pcb[ 4 ], *current = NULL;

void scheduler( ctx_t* ctx ) {

  if      ( current == &pcb[ 0 ] ) {
    memcpy( &pcb[ 0 ].ctx, ctx, sizeof( ctx_t ) );
    memcpy( ctx, &pcb[ 1 ].ctx, sizeof( ctx_t ) );
    current = &pcb[ 1 ];
  }
  else if ( current == &pcb[ 1 ] ) {
    memcpy( &pcb[ 1 ].ctx, ctx, sizeof( ctx_t ) );
    memcpy( ctx, &pcb[ 2 ].ctx, sizeof( ctx_t ) );
    current = &pcb[ 2 ];
  }
  else if ( current == &pcb[ 2 ] ) {
    memcpy( &pcb[ 2 ].ctx, ctx, sizeof( ctx_t ) );
    memcpy( ctx, &pcb[ 3 ].ctx, sizeof( ctx_t ) );
    current = &pcb[ 3 ];
  }
  else if ( current == &pcb[ 3 ] ) {
    memcpy( &pcb[ 3 ].ctx, ctx, sizeof( ctx_t ) );
    memcpy( ctx, &pcb[ 0 ].ctx, sizeof( ctx_t ) );
    current = &pcb[ 0 ];
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

  memset( &pcb[ 0 ], 0, sizeof( pcb_t ) );
  pcb[ 0 ].pid      = 0;
  pcb[ 0 ].ctx.cpsr = 0x50;
  pcb[ 0 ].ctx.pc   = ( uint32_t )( entry_PDef );
  pcb[ 0 ].ctx.sp   = ( uint32_t )(  &tos_PDef );

  memset( &pcb[ 1 ], 0, sizeof( pcb_t ) );
  pcb[ 1 ].pid      = 1;
  pcb[ 1 ].ctx.cpsr = 0x50;
  pcb[ 1 ].ctx.pc   = ( uint32_t )( entry_P0 );
  pcb[ 1 ].ctx.sp   = ( uint32_t )(  &tos_P0 );

  memset( &pcb[ 2 ], 0, sizeof( pcb_t ) );
  pcb[ 2 ].pid      = 2;
  pcb[ 2 ].ctx.cpsr = 0x50;
  pcb[ 2 ].ctx.pc   = ( uint32_t )( entry_P1 );
  pcb[ 2 ].ctx.sp   = ( uint32_t )(  &tos_P1 );

  memset( &pcb[ 3 ], 0, sizeof( pcb_t ) );
  pcb[ 3 ].pid      = 3;
  pcb[ 3 ].ctx.cpsr = 0x50;
  pcb[ 3 ].ctx.pc   = ( uint32_t )( entry_P2 );
  pcb[ 3 ].ctx.sp   = ( uint32_t )(  &tos_P2 );

  /* Once the PCBs are initialised, we (arbitrarily) select one to be
   * restored (i.e., executed) when the function then returns.
   */

  current = &pcb[ 0 ]; memcpy( ctx, &current->ctx, sizeof( ctx_t ) );

  TIMER0->Timer1Load     = 0x00100000; // select period = 2^20 ticks ~= 1 sec
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

    scheduler(ctx);
    // PL011_putc( UART0, 'K' );
    // PL011_putc( UART0, '<' );
    // PL011_putc( UART0,  x  );
    // PL011_putc( UART0, '>' );
    // PL011_putc( UART0, '\n' );
    // PL011_putc( UART0, '\n' );
    // PL011_putc( UART0, '\n' );
    // PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );PL011_putc( UART0, '\n' );

    UART0->ICR = 0x10;
  } else {
    PL011_putc( UART0, '\n' );
  }

  // Step 5: write the interrupt identifier to signal we're done.

  GICC0->EOIR = id;
}
