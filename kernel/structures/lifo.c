#include "lifo.h"

queue_t* lifo_init(){
  queue_t *lifo;
  memset( lifo, 0, sizeof( queue_t ) );
  // lifo = queue_init(MAX_SIZE);
  return lifo;
}

int lifo_peek(queue_t* lifo){
  return queue_front(lifo);
}

int lifo_pop(queue_t* lifo){
  int front = queue_front(lifo);
  queue_remove(lifo);
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
