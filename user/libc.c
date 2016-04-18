#include "libc.h"

void append_char(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

void yield() {
  asm volatile( "svc #0     \n"  );
}


void lib_fork(){
  asm volatile( "svc #10     \n"  );
}
void lib_exit(){
  asm volatile( "svc #11     \n"  );
}

int write( int fd, void* x, size_t n ) {
  int r;

  asm volatile( "mov r0, %1 \n"
                "mov r1, %2 \n"
                "mov r2, %3 \n"
                "svc #1     \n"
                "mov %0, r0 \n"
              : "=r" (r)
              : "r" (fd), "r" (x), "r" (n)
              : "r0", "r1", "r2" );

  return r;
}
char read_char() {
  char return_char;
  asm volatile( "svc #2     \n");

  int is_waiting_for_char = 1;
  while(is_waiting_for_char) {
    asm volatile("svc #3     \n"
                  "mov %0, r0 \n"
                : "=r" (return_char));
    if(return_char != '0'){
      is_waiting_for_char = 0;
    }
  }
  return return_char;
}
void read_line(char *string_from_buffer) {
  char termination_char = '\r';
  asm volatile( "svc #2     \n");
  int is_waiting_for_char = 1;
  while(is_waiting_for_char) {
    char return_char;
    asm volatile("svc #3     \n"
                  "mov %0, r0 \n"
                : "=r" (return_char));
    if(return_char == '0'){
        // Do nothing
    } else if(return_char == termination_char){
      is_waiting_for_char = 0;
    } else {
      append_char(string_from_buffer, return_char);
    }
  }
  return;
}
const static uint32_t i32_tab[10] = {
           1u,
          10u,
         100u,
        1000u,
       10000u,
      100000u, /* 10^ 5 */
     1000000u,
    10000000u,
   100000000u,
  1000000000u, /* 10^9  */
};

void uint32_to_string(char *out, uint32_t in) {
  int i;
  uint32_t tenpow;
  char accum;

  for (i = 9;i > 0;i--)
    if (in >= i32_tab[i]) break;

  do {
    tenpow = i32_tab[i];
    accum = '0';

    while (in >= tenpow) {
      in -= tenpow;
      accum++;
    }

    *out++ = accum;

  } while (i --> 0);

  *out = '\0';
}
void int_to_string(char* out, int in) {
  char rChar = in + '0';
  out = &rChar;
}
void write_str(char *string){
  write( 0, string, strlen(string));
}
