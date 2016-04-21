#include "filesys.h"
supernode_t supnode;
int next_free_address = 0;
int next_free_id = 0;
int write_object(void *object, int size, int addresses[], int fromAddr){
    char buffer[size];
    unsigned char* obj_char= (unsigned char*)object;
    memset( &buffer, 0, sizeof( buffer ) );
    const unsigned char *byte;

    // get bytes
    int pos = 0;
    int sizeCopy = size;
    for ( byte = obj_char; sizeCopy--; ++byte ){
        buffer[pos] = *byte;
        pos++;
    }

    // Number of blocks
    int addressIncrNum;
    int block_number = (size % 16) ? ((size / 16) + 1) : (size / 16);
    for ( int i = 0; i < block_number; i++){
      disk_wr( fromAddr, (uint8_t*)(&(buffer[ i * 16])), WRITE_SIZE );
      addresses[i] = fromAddr;
      fromAddr += ADDRESS_INCREMENT;
      addressIncrNum += 1;
    }
    return addressIncrNum;
}
void createFile(char name[20], int type, int parentId, void* data, int dataSize){

  // Create new inode
  inode_t newnode;
  memset( &newnode, 0, sizeof( inode_t ) );

  // Add in new node properties
  newnode.id = next_free_id;
  newnode.type = type;
  newnode.parentId = parentId;
  strcpy(newnode.name, name);
  next_free_id += 1;

  // Write object
  int addresses[100];
  int addressNum = write_object(data, dataSize, addresses, next_free_address);

  // Update next free address
  int lastAddress = addresses[addressNum - 1];
  next_free_address = lastAddress;

  // Set table data to point newly written data
  table_t data_table;
  memset( &data_table, 0, sizeof( table_t ) );
  for (int i = 0; i < 9; i++){
      data_table.datablocks[i] = addresses[i];
  }
  // TODO: Add table_t pointers

  // Update nodes addresses
  newnode.data_table = data_table;

  // Write inode
  int addressNumInode = write_object(&newnode, sizeof(inode_t), addresses, next_free_address);

  // Update next free address
  lastAddress = addresses[addressNumInode - 1];
  next_free_address = lastAddress;
}


void files_init(){
  char data[20] = "hello";
  createFile("rootfolder", 2, 0, &data, 20);

    // Init root node
    // inode_t rootnode;
    // memset( &rootnode, 0, sizeof( inode_t ) );
    // rootnode.id = 0;
    // rootnode.parentId = 0;
    // rootnode.type = 2;
    // rootnode.name = "root";
    //
    // int addresses[100];
    // int addressNum = write_object(&rootnode, sizeof(inode_t), addresses, 0);
    //
    //
    //
    //
    // memset( &supnode, 0, sizeof( supernode_t ) );
    // supnode.info = 6;
    // supnode.other = 3;
    // supnode.a = 1;
    // supnode.b = 1;
    // supnode.c = 1;
    // supnode.d = 1;
    // int addresses[100];
    // write_object(&supnode, sizeof(supernode_t), addresses);
    //
    // // 0 for p1, 10 for p2
    // // supernode_t newNode = *(supernode_t*)buffer;
    // // printf("newnode: %d\n", newNode.info);

}

int main(){
  files_init();

  // printf("size: %lu \n", sizeof(buffer));
  // printf("size: %lu \n", sizeof(supnode));
  // printf("size: %lu \n", sizeof(supnode.info));
  // printf("size: %lu \n", sizeof(int));

}
