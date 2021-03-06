#include "PDef.h"


void PDef() {
  int x = 0;
  // queue_t *lifo;
  // lifo_init(lifo);
  write_str("Outputting blocknum:");
  int block_num = disk_get_block_num();
  char *str;
  uint32_to_string(str, block_num);
  write_str(str); write_str("\n");

  write_str("Outputting blocklen:");
  int block_len = disk_get_block_len();
  uint32_to_string(str, block_len);
  write_str(str);

  int chanToThree = get_channel_id_to(3);
  PL011_putc( UART0, chanToThree + '0' );
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
    } else {
      write_str_raw("Unknown command");
    }
  }

  return;
}
void (*entry_PDef)() = &PDef;
