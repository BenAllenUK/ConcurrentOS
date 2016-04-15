#include "queues.h"
/* crateQueue function takes argument the maximum number of elements the Queue can hold, creates
a Queue according to it and returns a pointer to the Queue. */
Queue * queue_init(int maxElements)
{
  /* Create a Queue */
  Queue *Q;
  memset( Q, 0, sizeof( Queue ) );
  // Q = (Queue *)malloc(sizeof(Queue));
  /* Initialise its properties */
  memset( *(Q->elements), 0, sizeof(int)*maxElements );
  // Q->elements = (int *)malloc(sizeof(int)*maxElements);
  Q->size = 0;
  Q->capacity = maxElements;
  Q->front = 0;
  Q->rear = -1;
  /* Return the pointer */
  return Q;
}
void queue_remove(Queue *Q)
{
  /* If Queue size is zero then it is empty. So we cannot pop */
  if(Q->size==0)
  {
    // printf("Queue is Empty\n");
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
void queue_remove_end(Queue *Q){
  /* If Queue size is zero then it is empty. So we cannot pop */
  if(Q->size==0)
  {
    // printf("Queue is Empty\n");
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
int queue_front(Queue *Q){
  if(Q->size==0){
    // printf("Queue is Empty\n");

  }
  /* Return the element which is at the front*/
  return Q->elements[Q->front];
}
int queue_back(Queue *Q){
  if(Q->size==0){
    // printf("Queue is Empty\n");
  }
  return Q->elements[Q->rear];
}
void queue_add(Queue *Q,int element)
{
  /* If the Queue is full, we cannot push an element into it as there is no space for it.*/
  if(Q->size == Q->capacity)
  {
    // printf("Queue is Full\n");
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
//   Queue *Q = queue_init(5);
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
