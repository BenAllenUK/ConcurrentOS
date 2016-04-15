#ifndef __FIFO_H
#define __FIFO_H

#include<stdio.h>
#include<stdlib.h>

#include <stddef.h>
#include <stdint.h>

#include <string.h>

#include "queues.h"

#define MAX_SIZE 10


queue_t* fifo_init();
int fifo_peek(queue_t* fifo);
void fifo_push(queue_t* fifo,int number);
int fifo_pop(queue_t* fifo);

#endif
