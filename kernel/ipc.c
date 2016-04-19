#include "ipc.h"
channel_t channels[ MAX_CHANNELS ];
int channel_count = 0;

void ipc_init(int to_id, int from_id){
  int new_channel_id = channel_count;

  if (new_channel_id < MAX_CHANNELS){
    memset( &channels[ new_channel_id ], 0, sizeof( channel_t ) );
    channels[ new_channel_id ].id = new_channel_id;
    channels[ new_channel_id ].processA = to_id;
    channels[ new_channel_id ].processB = from_id;

    fifo_init(&(channels[ new_channel_id ].dataAtoB));
    fifo_init(&(channels[ new_channel_id ].dataBtoA));

    channel_count++;
  }

}
int ipc_get_channel_id(int from_id, int to_id){
  for (int i = 0; i < channel_count; i++){
    if (channels[i].processA == from_id && channels[i].processB == to_id){
      return channels[i].id;
    } else if (channels[i].processB == from_id && channels[i].processA == to_id){
      return channels[i].id;
    }
  }
}
void ipc_push(int chan_id, int to_id, int data){
  if (to_id == channels[chan_id].processA) {
    fifo_push(&(channels[chan_id].dataBtoA), data);
  } else if (to_id == channels[chan_id].processB) {
    fifo_push(&(channels[chan_id].dataAtoB), data);
  }
}

int ipc_pull(int chan_id, int from_id){
  int val = -1;
  while (val == -1){
    if (from_id == channels[chan_id].processA) {
      val = fifo_pop(&(channels[chan_id].dataAtoB));
    } else if (from_id == channels[chan_id].processB) {
      val = fifo_pop(&(channels[chan_id].dataBtoA));
    }
  }
  return val;
}
