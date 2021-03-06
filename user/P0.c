#include "P0.h"

int is_prime( uint32_t x ) {
  if ( !( x & 1 ) || ( x < 2 ) ) {
    return ( x == 2 );
  }

  for( uint32_t d = 3; ( d * d ) <= x ; d += 2 ) {
    if( !( x % d ) ) {
      return 0;
    }
  }

  return 1;
}

void P0() {
  int x = 0;

  while( 1 ) {
    // test whether each x for 2^8 < x < 2^24 is prime or not

    for( uint32_t x = ( 1 << 8 ); x < ( 1 << 24 ); x++ ) {
      int r = is_prime( x );

      char *rAsString;
      int_to_string(rAsString, r);

      char *xAsString;
      uint32_to_string(xAsString, x);

      write_str("P0: ");
      write_str("is_prime( ");
      write_str(xAsString);
      write_str(" ) = ");
      write_str(rAsString);
      write_str("\n");
    }
  }

  return;
}
void (*entry_P0)() = &P0;
