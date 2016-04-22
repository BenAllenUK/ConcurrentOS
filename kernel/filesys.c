#include "filesys.h"
supernode_t supnode;
int next_free_address = 0;
int next_free_id = 0;
int root_addr;
int root_inode_addr;


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
void read_object(int size, int fromAddr, char buffer[]){
  int addressFrom = fromAddr;
  int block_number = (size % 16) ? ((size / 16) + 1) : (size / 16);
  for ( int i = 0; i < block_number; i++){
    disk_rd( addressFrom, (uint8_t*)(&(buffer[ i * 16 ])), WRITE_SIZE );
    addressFrom += ADDRESS_INCREMENT;
  }
}
void readFile(int address, inode_t *output){
  char response[sizeof(inode_t)];
  memset( &response, 0, sizeof(inode_t) );
  read_object(sizeof(inode_t), address, response);
  inode_t content = *(inode_t*)response;
  memcpy(output, &content, sizeof(inode_t));
}
int createFile(int address, int id, char name[20], int type, int parentId, void* data, int dataSize, int *inodeAddress){

  // Create new inode
  inode_t newnode;
  memset( &newnode, 0, sizeof( inode_t ) );

  // Add in new node properties
  newnode.id = id;
  newnode.type = type;
  newnode.parentId = parentId;
  strcpy(newnode.name, name);


  // Write object
  int addresses[100];
  memset( &addresses, 0, sizeof( int ) * 100 );
  int addressNum = write_object(data, dataSize, addresses, address);


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
  int next_address = addresses[addressNum - 1] + ADDRESS_INCREMENT;
  *inodeAddress = next_address;
  int addressNumInode = write_object(&newnode, sizeof(inode_t), &(addresses[addressNum]), next_address);




  return addresses[addressNum + addressNumInode - 1]; // The last address
}

void updateFolderWithAddress(int folderDataAddr, int folderInode, int newFileInode){
  // Read exisiting
  inode_t response;
  memset( &response, 0, sizeof(inode_t) );
  readFile(folderInode, &response);

  // Create the new data object
  int links2[20];
  memcpy( &links2, response.data_table.datablocks, sizeof(int) * 20 );
  for( int i = 0; i < 9; i++){
      if(links2[i] == 0){
          links2[0] = newFileInode;
      }

  }



  // Save over the top of the other file
  int oldAddress = 0;
  createFile(folderDataAddr, response.id, response.name, response.type, response.parentId, &links2, 20, &oldAddress);
  inode_t secondResponse;
  memset( &secondResponse, 0, sizeof(inode_t) );
  readFile(folderInode, &secondResponse);

  // Read file contents
  // char response[20];
  // memset( &response, 0, sizeof(int) * 20 );
  // read_object(sizeof(int) * 20, &secondResponse.data_table[0], response);
}

void files_init(){
  char data[20] = "hello";
  int links[20];
  memset( &links, 0, sizeof(int) * 20 );


  int inodeAddress = 0;
  root_addr = next_free_address;
  int lastAddress = createFile(next_free_address, next_free_id,"rootfolder", 2, 0, &links, 20, &inodeAddress);
  root_inode_addr = inodeAddress;
  next_free_address = lastAddress + ADDRESS_INCREMENT;
  next_free_id += 1;

  // Create file
  int fileInodeAddress = 0;
  lastAddress = createFile(next_free_address, next_free_id,"rootfile", 1, 0, &data, 20, &fileInodeAddress);
  next_free_address = lastAddress + ADDRESS_INCREMENT;
  next_free_id += 1;

  // When updating:
  updateFolderWithAddress(root_addr, root_inode_addr, fileInodeAddress);


  // Now update
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
