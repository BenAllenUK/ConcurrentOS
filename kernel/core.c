#include "core.h"

int time_slices_left = 0;
int core_process_finished(){
  return time_slices_left == 0;
}
// void core_init(queue_t *pcb_queue, pcb_t *pcb[]){
//
// }
void core_exit(queue_t *pcb_queue, pcb_t *pcb, int current_focus){
  // int current_pid = fifo_pop(pcb_queue);
  // fifo_pop(current_focus);
  if (current_focus != 1) {
    // Remove current focus
    for ( int i = 0; i < fifo_size(pcb_queue); i++ ){
      int this_element = fifo_pop(pcb_queue);
      if(this_element != current_focus){
        fifo_push(pcb_queue, this_element);
      }
    }
    memset( &pcb[ current_focus ], 0, sizeof( pcb_t ) );
    clear();
    write_str_raw("Exited process\n");
    show_display();
  } else {
    clear();
    show_display();
  }
}
void core_fork(queue_t *pcb_queue, pcb_t *pcb, int current_focus){

  int num_pcb = fifo_size(pcb_queue) + 1;

  // Space for another process
  if(num_pcb < MAX_PROCCESORS){

    pcb[num_pcb] = pcb[current_focus];
    memcpy( &pcb[num_pcb].ctx, &pcb[current_focus].ctx, sizeof( ctx_t ) );
    pcb[num_pcb].stats.parentId = current_focus;
    pcb[num_pcb].ctx.sp = top_of_stack;
    pcb[num_pcb].stats.priority = pcb[current_focus].stats.priority;
    pcb[num_pcb].pid = num_pcb;
    fifo_push(pcb_queue, num_pcb);
    top_of_stack += STACK_SIZE;

    write_str_raw("Forked process ");
    PL011_putc( UART0, current_focus + '0' );
    write_str_raw(" to ");
    PL011_putc( UART0, num_pcb  + '0');
    write_str_raw("\n");
  } else {
    write_str_raw("Process not forked - max limit reached");
  }
}


void core_save(queue_t *pcb_queue, pcb_t *pcb, ctx_t *ctx){
  // // Switch process
  int current_pid = pcb[ fifo_peek(pcb_queue) ].pid;

  // Save and then add back to queue at the end
  memcpy( &pcb[ fifo_pop(pcb_queue) ].ctx, ctx, sizeof( ctx_t ) );
  fifo_push(pcb_queue, current_pid);
}
void core_new(queue_t *pcb_queue, pcb_t *pcb, ctx_t *ctx){
  memcpy( ctx, &pcb[ fifo_peek(pcb_queue) ].ctx, sizeof( ctx_t ) );
  time_slices_left = pcb[ fifo_peek(pcb_queue) ].stats.priority;
  pcb[ fifo_peek(pcb_queue) ].stats.age += 1;
}
void core_decrease_time(){
  time_slices_left--;
}
