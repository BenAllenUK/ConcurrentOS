#ifndef __PDef_H
#define __PDef_H

#include <stddef.h>
#include <stdint.h>

#include "libc.h"
#include "PL011.h"
#include "ipc.h"

#include "structures/lifo.h"
#include "disk.h"

// define symbols for P1 entry point and top of stack
extern void (*entry_PDef)();
extern uint32_t tos_PDef;

#endif
