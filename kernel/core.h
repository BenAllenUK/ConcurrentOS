#ifndef __CORE_H
#define __CORE_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "constants.h"
#include "structures/fifo.h"
#include "structures/lifo.h"
#include "structures/queues.h"
int core_process_finished();
// void core_init(queue_t *pcb_queue, pcb_t *pcb[]);
void core_fork(queue_t *pcb_queue, pcb_t *pcb);
void core_exit(queue_t *pcb_queue, pcb_t *pcb);
void core_save(queue_t *pcb_queue, pcb_t *pcb, ctx_t *ctx);
void core_new(queue_t *pcb_queue, pcb_t *pcb, ctx_t *ctx);
void core_decrease_time();
#endif
