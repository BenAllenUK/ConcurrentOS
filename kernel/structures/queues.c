#include "queues.h"
/* cratequeue_t function takes argument the maximum number of elements the queue_t can hold, creates
a queue_t according to it and returns a pointer to the queue_t. */
void queue_init(queue_t* Q, int maxElements)
{
  /* Create a queue_t */
  // memset( Q, 0, sizeof( queue_t ) );
  // Q = (queue_t *)malloc(sizeof(queue_t));
  /* Initialise its properties */
  // memset( Q->elements, 0, sizeof(int)*10 );
  // Q->elements = (int *)malloc(sizeof(int)*maxElements);
  
  /* Return the pointer */

}
void queue_remove(queue_t *Q)
{
  /* If queue_t size is zero then it is empty. So we cannot pop */
  if(Q->size==0)
  {
    // printf("queue_t is Empty\n");
    return;
  }
  /* Removing an element is equivalent to incrementing index of front by one */
  else
  {
    Q->size--;
    Q->front++;
    /* As we fill elements in circular fashion */
    if(Q->front==Q->capacity)
    {
      Q->front=0;
    }
  }
  return;
}
void queue_remove_end(queue_t *Q){
  /* If queue_t size is zero then it is empty. So we cannot pop */
  if(Q->size==0)
  {
    // printf("queue_t is Empty\n");
    return;
  }
  /* Removing an element is equivalent to incrementing index of front by one */
  else
  {
    Q->size--;
    Q->front++;
    /* As we fill elements in circular fashion */
    if(Q->front==Q->capacity)
    {
      Q->front=0;
    }
  }
  return;
}
int queue_front(queue_t *Q){
  if(Q->size==0){
    // printf("queue_t is Empty\n");

  }
  /* Return the element which is at the front*/
  return Q->elements[Q->front];
}
int queue_back(queue_t *Q){
  if(Q->size==0){
    // printf("queue_t is Empty\n");
  }
  return Q->elements[Q->rear];
}
void queue_add(queue_t *Q,int element)
{
  /* If the queue_t is full, we cannot push an element into it as there is no space for it.*/
  if(Q->size == Q->capacity)
  {
    // printf("queue_t is Full\n");
  }
  else
  {
    Q->size++;
    Q->rear = Q->rear + 1;
    /* As we fill the queue in circular fashion */
    if(Q->rear == Q->capacity)
    {
      Q->rear = 0;
    }
    /* Insert the element in its rear side */
    Q->elements[Q->rear] = element;
  }
  return;
}
// int queue_main()
// {
//   queue_t *Q = queue_init(5);
//   queue_add(Q,1);
//   queue_add(Q,2);
//   queue_add(Q,3);
//   queue_add(Q,4);
//   // printf("Front element is %d\n",queue_front(Q));
//   queue_add(Q,5);
//   queue_remove(Q);
//   queue_add(Q,6);
//   printf("Front element is %d\n",queue_front(Q));
//   return 0;
// }
