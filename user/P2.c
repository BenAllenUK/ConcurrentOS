#include "P2.h"

uint32_t weight( uint32_t x ) {
  x = ( x & 0x55555555 ) + ( ( x >>  1 ) & 0x55555555 );
  x = ( x & 0x33333333 ) + ( ( x >>  2 ) & 0x33333333 );
  x = ( x & 0x0F0F0F0F ) + ( ( x >>  4 ) & 0x0F0F0F0F );
  x = ( x & 0x00FF00FF ) + ( ( x >>  8 ) & 0x00FF00FF );
  x = ( x & 0x0000FFFF ) + ( ( x >> 16 ) & 0x0000FFFF );

  return x;
}

void P2() {
  int num = 0;
  int count = 0;

  int chan = get_channel_id_to(2);

  while( 1 ) {
    // compute the Hamming weight of each x for 2^8 < x < 2^24
    num++;

    if(num > 7983590){
      num = 0;
      count++;
    }
    char *rAsString;


    write_str("P2: ");
    uint32_to_string(rAsString, count);
    write_str(rAsString);
    write_str(" ");
    uint32_to_string(rAsString, num);
    write_str(rAsString);
    write_str("\n");

    if(num > 200000){
      write_str("Pushing");
      ipc_push(chan, 2, 10);
      num = 0;
    }

    // for( uint32_t x = ( 1 << 8 ); x < ( 1 << 24 ); x++ ) {
    //   uint32_t r = weight( x );  // printf( "weight( %d ) = %d\n", x, r );
    //
    //   char *xAsString;
    //   char *rAsString;
    //   uint32_to_string(xAsString, x);
    //   uint32_to_string(rAsString, r);
    //
    //   write_str("P2: ");
    //   write_str("weight( ");
    //   write_str(xAsString);
    //   write_str(" ) = ");
    //   write_str(rAsString);
    //   write_str("\n");
    //
    // }
  }

  return;
}
void (*entry_P2)() = &P2;
