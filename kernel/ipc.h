#ifndef __IPC_H
#define __IPC_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "constants.h"
#include "structures/fifo.h"
#include "structures/lifo.h"
#include "structures/queues.h"
#include "PL011.h"
#include "libc.h"

typedef struct {
  int id;
  int processA;
  int processB;
  queue_t dataAtoB;
  queue_t dataBtoA;
} channel_t;

void ipc_init(int to_id, int from_id);
int ipc_get_channel_id(int from_id, int to_id);
void ipc_push(int chan_id, int to_id, int data);
int ipc_pull(int chan_id, int from_id);
#endif
