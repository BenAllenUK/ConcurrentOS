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
typedef struct
{
        int capacity;
        int size;
        int front;
        int rear;
        int elements[10];
} queue_t;

void queue_init(queue_t *Q, int maxElements);
void queue_remove(queue_t *Q);
void queue_remove_end(queue_t *Q);
int queue_front(queue_t *Q);
int queue_end(queue_t *Q);
void queue_add(queue_t *Q,int element);
int queue_size(queue_t *Q);
#endif
