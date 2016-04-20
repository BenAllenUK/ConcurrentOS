#ifndef __FILESYS_H
#define __FILESYS_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "constants.h"
#include "../device/disk.h"
// #include "disk.h"
#define WRITE_SIZE 16

typedef struct {
  int info;
  int other;
} supernode_t;


void files_init();
#endif
