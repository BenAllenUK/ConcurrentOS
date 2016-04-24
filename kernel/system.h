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
#define TYPE_FILE 1
#define TYPE_FOLDER 2

#define DATA_OFFSET 100

#define DATA_SIZE 32


void system_init();
void system_read_object(char buffer[], int size, int fromAddr);
void system_write_object(void *object, int size, int fromAddr);
void system_new_write_file(int id, char name[16], void *data);
void system_update_folder(int new_link);
void system_new_write_folder(int id, char name[16]);

typedef struct {
  char s;
  int id; // 4
  int parentId; // 4
  int type; // 4
  char name[16]; // 16
  int datablocks[8];
  int datablocks_length;
  char e;
} node_t;

#endif
