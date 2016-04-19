#include "PDef.h"


void PDef() {
  int x = 0;

  // queue_t *lifo;
  // lifo_init(lifo);

  while( 1 ) {
    // lifo_push(lifo, 1);
    // lifo_push(lifo, 2);
    // int r1 = lifo_pop(lifo);
    // int r2 = lifo_pop(lifo);
    // PL011_putc( UART0, r1 + '0' );
    // PL011_putc( UART0, ' ' );

    // PL011_putc( UART0, return_char );
    char return_string[256] = "";
    read_line(return_string);

    if (str_match(return_string,"fork") == 1){
      lib_fork();
    } else if (str_match(return_string,"exit") == 1){
      lib_exit();
    }
    write_str_raw("\n Entered: ");
    write_str_raw(return_string);
    write_str_raw("\n");
  }

  return;
}
void (*entry_PDef)() = &PDef;
