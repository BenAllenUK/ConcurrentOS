#include "fifo.h"

fifo_t* fifo_init(){
  fifo_t *fifo;
  memset( fifo, 0, sizeof( fifo_t ) );
  fifo->queue = queue_init(MAX_SIZE);
  return fifo;
}

int fifo_peek(fifo_t* fifo){
  return queue_front(fifo->queue);
}

int fifo_pop(fifo_t* fifo){
  int front = queue_front(fifo->queue);
  queue_remove(fifo->queue);
  return front;
}

void fifo_push(fifo_t* fifo,int number){
  queue_add(fifo->queue, number);
}

// int fifo_main()
// {
//         fifo_t *fifo = fifo_init();
//         fifo_push(fifo, 1);
//         fifo_push(fifo, 2);
//         fifo_push(fifo, 3);
//         printf("Front element is %d\n",fifo_pop(fifo));
//         printf("Front element is %d\n",fifo_pop(fifo));
//         printf("Front element is (pee) %d\n",fifo_peek(fifo));
//         fifo_push(fifo, 4);
//         printf("Front element is %d\n",fifo_pop(fifo));
//         printf("Front element is %d\n",fifo_pop(fifo));
//         fifo_push(fifo, 5);
//         fifo_push(fifo, 6);
//         fifo_push(fifo, 7);
//         printf("Front element is %d\n",fifo_pop(fifo));
//         printf("Front element is %d\n",fifo_pop(fifo));
//         printf("Front element is (pee) %d\n",fifo_peek(fifo));
//         fifo_push(fifo, 8);
//         printf("Front element is %d\n",fifo_pop(fifo));
//         printf("Front element is %d\n",fifo_pop(fifo));
//
//         return 0;
// }
