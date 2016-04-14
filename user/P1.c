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
  while( 1 ) {
    // compute the gcd between pairs of x and y for 2^4 < x, y < 2^8
    for( uint32_t x = ( 1 << 4 ); x < ( 1 << 8 ); x++ ) {
      for( uint32_t y = ( 1 << 4 ); y < ( 1 << 8 ); y++ ) {
        uint32_t r = gcd( x, y );  // printf( "gcd( %d, %d ) = %d\n", x, y, r );


        char *xAsString;
        char *yAsString;
        char *rAsString;
        uint32_to_string(xAsString, x);
        uint32_to_string(yAsString, y);
        uint32_to_string(rAsString, r);

        writeString("P1: ");
        writeString("gcd( ");
        writeString(xAsString);
        writeString(", ");
        writeString(yAsString);
        writeString(" ) = ");
        writeString(rAsString);
        writeString("\n");
      }
    }
  }

  return;
}
void (*entry_P1)() = &P1;
