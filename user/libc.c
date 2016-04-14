#include "libc.h"
void yield() {
  asm volatile( "svc #0     \n"  );
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
void writeString(char *string){
  write( 0, string, strlen(string));
}
