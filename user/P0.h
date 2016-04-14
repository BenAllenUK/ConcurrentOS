#ifndef __P0_H
#define __P0_H

#include <stddef.h>
#include <stdint.h>

#include "libc.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>



// define symbols for P1 entry point and top of stack
extern void (*entry_P0)();
extern uint32_t tos_P0;

#endif
