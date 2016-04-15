#include "lifo.h"

lifo_t* lifo_init(){
  lifo_t *lifo;
  memset( lifo, 0, sizeof( lifo_t ) );
  lifo->queue = queue_init(MAX_SIZE);
  return lifo;
}

int lifo_peek(lifo_t* lifo){
  return queue_front(lifo->queue);
}

int lifo_pop(lifo_t* lifo){
  int front = queue_front(lifo->queue);
  queue_remove(lifo->queue);
  return front;
}

void lifo_push(lifo_t* lifo,int number){
  queue_add(lifo->queue, number);
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
