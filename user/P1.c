#include "P1.h"

uint32_t gcd( uint32_t x, uint32_t y ) {
  if     ( x == y ) {
    return x;
  }
  else if( x >  y ) {
    return gcd( x - y, y );
  }
  else if( x <  y ) {
    return gcd( x, y - x );
  }
}

void P1() {

  int chan = get_channel_id_to(3);
  while( 1 ) {

    int pulled = ipc_pull(chan, 3);
    write_str("\n\n\n\n");
    PL011_putc( UART0, 'A' );
    PL011_putc( UART0, pulled + '0' );
    write_str("\n\n\n\n");
    // compute the gcd between pairs of x and y for 2^4 < x, y < 2^8
    // for( uint32_t x = ( 1 << 4 ); x < ( 1 << 8 ); x++ ) {
    //   for( uint32_t y = ( 1 << 4 ); y < ( 1 << 8 ); y++ ) {
    //     uint32_t r = gcd( x, y );  // printf( "gcd( %d, %d ) = %d\n", x, y, r );
    //
    //
    //     char *xAsString;
    //     char *yAsString;
    //     char *rAsString;
    //     uint32_to_string(xAsString, x);
    //     uint32_to_string(yAsString, y);
    //     uint32_to_string(rAsString, r);
    //
    //     write_str("P1: ");
    //     write_str("gcd( ");
    //     write_str(xAsString);
    //     write_str(", ");
    //     write_str(yAsString);
    //     write_str(" ) = ");
    //     write_str(rAsString);
    //     write_str("\n");
    //   }
    // }
  }

  return;
}
void (*entry_P1)() = &P1;
