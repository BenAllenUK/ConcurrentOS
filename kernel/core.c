#include "core.h"

int time_slices_left = 0;
int core_process_finished(){
  return time_slices_left == 0;
}
// void core_init(queue_t *pcb_queue, pcb_t *pcb[]){
//
// }
void core_exit(queue_t *pcb_queue, pcb_t *pcb){
  int current_pid = fifo_peek(pcb_queue);
}
void core_fork(queue_t *pcb_queue, pcb_t *pcb){
  int current_pid = fifo_peek(pcb_queue);
}
void core_save(queue_t *pcb_queue, pcb_t *pcb, ctx_t *ctx){
  // // Switch process
  int current_pid = pcb[ fifo_peek(pcb_queue) ].pid;
  //
  // // Save and then add back to queue at the end
  memcpy( &pcb[ fifo_pop(pcb_queue) ].ctx, ctx, sizeof( ctx_t ) );
  fifo_push(pcb_queue, current_pid);
}
void core_new(queue_t *pcb_queue, pcb_t *pcb, ctx_t *ctx){
  memcpy( ctx, &pcb[ fifo_peek(pcb_queue) ].ctx, sizeof( ctx_t ) );
  time_slices_left = pcb[ fifo_peek(pcb_queue) ].stats.priority;
}
void core_decrease_time(){
  time_slices_left--;
}
