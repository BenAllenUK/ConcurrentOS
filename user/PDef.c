#include "PDef.h"


void PDef() {
  int x = 0;

  queue_t *lifo;
  lifo_init(lifo);

  while( 1 ) {
    lifo_push(lifo, 1);
    lifo_push(lifo, 2);
    int r1 = lifo_pop(lifo);
    int r2 = lifo_pop(lifo);
    PL011_putc( UART0, r1 + '0' );
    PL011_putc( UART0, r1 + ' ' );
    PL011_putc( UART0, r2 + '0' );
    PL011_putc( UART0, r1 + '\n' );
  }

  return;
}
void (*entry_PDef)() = &PDef;
