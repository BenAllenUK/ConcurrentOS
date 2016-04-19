#ifndef __LIBC_H
#define __LIBC_H

#include <stddef.h>
#include <stdint.h>

#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include "PL011.h"
// cooperatively yield control of processor, i.e., invoke the scheduler
void yield();

// write n bytes from x to the file descriptor fd
int write( int fd, void* x, size_t n );
void lib_fork();
void lib_exit();
void uint32_to_string(char *out, uint32_t in);

void int_to_string(char *out, int in);

void write_str(char *string);
void write_int_raw(int i);
void write_str_raw(char *string);
void write_int(int i);
char read_char();
void clear();
int str_match(char* input,char* check);
void show_display();
void hide_display();

void read_line(char *string_from_buffer);
int get_channel_id_to(int pid);
#endif
