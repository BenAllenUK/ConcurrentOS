#include "PDef.h"


void PDef() {
  int x = 0;

  while( 1 ) {
      // Do nothing

    fifo_t *fifo = fifo_init();
    // fifo_push(fifo, 1);
    // fifo_push(fifo, 2);
    // fifo_push(fifo, 3);
    // writeString("Front element is: ");
    // char* numAsStr;
    // int_to_string(numAsStr, fifo_pop(fifo));
    // writeString(numAsStr);
    // writeString("\n");
    // char* numAsStr2;
    // int_to_string(numAsStr2, fifo_pop(fifo));
    // writeString("Front element is");
    // writeString(numAsStr2);
    // writeString("\n");
    //
    // fifo_push(fifo, 4);
    // writeString("Front element is (peek): ");
    // int_to_string(numAsStr2, fifo_peek(fifo));
    // writeString(numAsStr2);
    writeString("\n");

  }

  return;
}
void (*entry_PDef)() = &PDef;
