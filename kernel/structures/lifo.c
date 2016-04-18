#include "lifo.h"

int lifo_size(queue_t* lifo){
  return queue_size(lifo);
}


queue_t* lifo_init(queue_t* lifo){
  memset( lifo, 0, sizeof( queue_t ) );
  lifo->size = 0;
  lifo->capacity = 10;
  lifo->front = 0;
  lifo->rear = -1;
  return lifo;
}

int lifo_peek(queue_t* lifo){
  return queue_end(lifo);
}

int lifo_pop(queue_t* lifo){
  int front = queue_end(lifo);
  queue_remove_end(lifo);
  return front;
}

void lifo_push(queue_t* lifo,int number){
  queue_add(lifo, number);
}

// int lifo_main()
// {
//         lifo_t *lifo = lifo_init();
//         lifo_push(lifo, 1);
//         lifo_push(lifo, 2);
//         lifo_push(lifo, 3);
//         printf("Front element is %d\n",lifo_pop(lifo));
//         printf("Front element is %d\n",lifo_pop(lifo));
//         printf("Front element is (pee) %d\n",lifo_peek(lifo));
//         lifo_push(lifo, 4);
//         printf("Front element is %d\n",lifo_pop(lifo));
//         printf("Front element is %d\n",lifo_pop(lifo));
//
//         return 0;
// }
