#include "filesys.h"
supernode_t supnode;
char buffer[256];
void toBytes(const void *object, size_t size){
    const unsigned char *byte;
    int pos = 0;
      for ( byte = object; size--; ++byte ){
          // printf("%02X", *byte);
          buffer[pos] = *byte;
          pos++;
      }
      // putchar('\n');
}
void files_init(){


    memset( &supnode, 0, sizeof( supernode_t ) );
    supnode.info = 6;
    supnode.other = 3;

    unsigned char* ptr= (unsigned char*)&supnode;
    toBytes(ptr, sizeof(supnode));

    disk_wr( 0, (uint8_t*)(&buffer), WRITE_SIZE );
}

int main(){
  files_init();

  // printf("size: %lu \n", sizeof(buffer));
  // printf("size: %lu \n", sizeof(supnode));
  // printf("size: %lu \n", sizeof(supnode.info));
  // printf("size: %lu \n", sizeof(int));

}
