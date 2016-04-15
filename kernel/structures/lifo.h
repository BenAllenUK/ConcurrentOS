#ifndef __LIFO_H
#define __LIFO_H

#include<stdio.h>
#include<stdlib.h>

#include <stddef.h>
#include <stdint.h>

#include <string.h>

#include "queues.h"

#define MAX_SIZE 10

typedef struct
{
        Queue* queue;
} lifo_t;

lifo_t* lifo_init();
int lifo_peek(lifo_t* lifo);
void lifo_push(lifo_t* lifo,int number);

#endif
