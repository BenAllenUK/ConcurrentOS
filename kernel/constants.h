#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define TIMER_INTERVAL 0x00100000
#define MAX_PROCCESORS 10
#define ENTRY_CHAR 'Q'
#define EXIT_CHAR 'E'

typedef struct {
  uint32_t cpsr, pc, gpr[ 13 ], sp, lr;
} ctx_t;

typedef struct {
  uint32_t priority, parentId;
} stats_t;

typedef int pid_t;

typedef struct {
  pid_t pid;
  ctx_t ctx;
  stats_t stats;
} pcb_t;

#endif
