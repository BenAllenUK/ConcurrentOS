#ifndef __QUEUES_H
#define __QUEUES_H

#include<stdio.h>
#include<stdlib.h>

#include <stddef.h>
#include <stdint.h>

#include <string.h>

/*Queue has five properties. capacity stands for the maximum number of elements Queue can hold.
  Size stands for the current size of the Queue and elements is the array of elements. front is the
 index of first element (the index at which we remove the element) and rear is the index of last element
 (the index at which we insert the element) */
typedef struct Queue
{
        int capacity;
        int size;
        int front;
        int rear;
        int *elements;
} Queue;

Queue * queue_init(int maxElements);
void queue_remove(Queue *Q);
int queue_front(Queue *Q);
void queue_add(Queue *Q,int element);

#endif
