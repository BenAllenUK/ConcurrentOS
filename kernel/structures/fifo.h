#ifndef __FIFO_H
#define __FIFO_H

#include<stdio.h>
#include<stdlib.h>

#include <stddef.h>
#include <stdint.h>

#include <string.h>

#include "queues.h"

#define MAX_SIZE 10

typedef struct {
  Queue* queue;
} fifo_t;

fifo_t* fifo_init();
int fifo_peek(fifo_t* fifo);
void fifo_push(fifo_t* fifo,int number);
int fifo_pop(fifo_t* fifo);

#endif
