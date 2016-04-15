#include "fifo.h"

queue_t* fifo_init(queue_t* fifo){
  memset( fifo, 0, sizeof( queue_t ) );
  fifo->size = 0;
  fifo->capacity = 10;
  fifo->front = 0;
  fifo->rear = -1;
  return fifo;
}

int fifo_peek(queue_t* fifo){
  return queue_front(fifo);
}

int fifo_pop(queue_t* fifo){
  int front = queue_front(fifo);
  queue_remove(fifo);
  return front;
}

void fifo_push(queue_t* fifo,int number){
  queue_add(fifo, number);
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
