#include "PDef.h"


void PDef() {
  int x = 0;

  queue_t *fifo;
  fifo_init(fifo);

  while( 1 ) {
    fifo_push(fifo, 1);
    fifo_push(fifo, 2);
    int r1 = fifo_pop(fifo);
    int r2 = fifo_pop(fifo);
    PL011_putc( UART0, r1 + '0' );
    PL011_putc( UART0, r2 + '0' );


  }

  return;
}
void (*entry_PDef)() = &PDef;
