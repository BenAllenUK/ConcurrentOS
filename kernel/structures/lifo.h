#ifndef __LIFO_H
#define __LIFO_H

#include<stdio.h>
#include<stdlib.h>

#include <stddef.h>
#include <stdint.h>

#include <string.h>

#include "queues.h"

#define MAX_SIZE 10


queue_t* lifo_init();
int lifo_peek(queue_t* lifo);
void lifo_push(queue_t* lifo,int number);
int lifo_pop(queue_t* lifo);

#endif
