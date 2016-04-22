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
#define ADDRESS_INCREMENT 1

typedef struct {
  int info;
  int other;
  int d;
  int a;
  int b;
  int c;

} supernode_t;

typedef struct {
  char a = '[';
  int datablocks[9];
  char b = ']';
} table_t;

typedef struct {
  char p = '(';
  int id; // 4
  int parentId; // 4
  int type; // 4
  char name[20]; // 20
  table_t data_table; // 4 * 9
  table_t *single_table; // 4
  table_t **double_table; // 4
  table_t ***triple_table; // 4
  char p = ')';
} inode_t;


void files_init();
#endif
