#include "system.h"

int id = 0;


int start_node_address = 0;
int start_data_address = DATA_OFFSET;
int folder_pos;

void system_init(){
  char file_data[DATA_SIZE] = "Hello World";
  system_write_object(file_data, DATA_SIZE, 0);

  char *readBuffer;
  system_read_object(readBuffer, DATA_SIZE, 0);

  // char data[DATA_SIZE] = "Hello World";
  //
  // system_new_write_folder(0, "Hi");
  // system_new_write_file(0, "file", data);

  // char otherData[DATA_SIZE] = "This is a test";
  // system_new_write_file(0, "file", otherData);

}

void system_read_object(char buffer[], int size, int fromAddr){
  int addressFrom = fromAddr;
  int block_number = (size % 16) ? ((size / 16) + 1) : (size / 16);
  for ( int i = 0; i < block_number; i++){
    disk_rd( addressFrom, (uint8_t*)(&(buffer[ i * 16 ])), WRITE_SIZE );
    addressFrom += ADDRESS_INCREMENT;
  }
}

void system_write_object(void *object, int size, int fromAddr){
  char buffer[size];
  memset( &buffer, 0, sizeof( size ) );
  unsigned char* obj_char= (unsigned char*)object;

  const unsigned char *byte;
  int pos = 0;
  int sizeCopy = size;
  int addressCopy = fromAddr;
  for ( byte = obj_char; sizeCopy--; ++byte ){
      buffer[pos] = *byte;
      pos++;
  }

  int block_number = (size % 16) ? ((size / 16) + 1) : (size / 16);
  for ( int i = 0; i < block_number; i++){
    disk_wr( addressCopy, (uint8_t*)(&(buffer[ i * 16])), WRITE_SIZE );
    addressCopy += ADDRESS_INCREMENT;
  }
}

void system_new_write_file(int id, char name[16], void *data){
  node_t new_file;
  memset( &new_file, 0, sizeof( node_t ) );
  new_file.s = '('; new_file.e = ')'; new_file.parentId = 0;
  new_file.id = id;
  new_file.type = TYPE_FILE;
  strcpy(new_file.name, name);
  new_file.datablocks[0] = start_data_address;
  new_file.datablocks_length = 1;

  // Write Node
  system_write_object(&new_file, sizeof(node_t), start_node_address);

  // Write Data
  system_write_object(data, DATA_SIZE, start_data_address);

  // Update folder
  system_update_folder(start_node_address);

  // Add to addresses since it is a new write
  start_node_address += (sizeof(node_t) % WRITE_SIZE) ? ((sizeof(node_t) / WRITE_SIZE) + 1) : (sizeof(node_t) / WRITE_SIZE);
  start_data_address += DATA_SIZE / WRITE_SIZE;
}

void system_update_folder(int new_link){
  char readBuffer;
  memset( &readBuffer, 0, sizeof( node_t ) );
  system_read_object(&readBuffer, sizeof(node_t), folder_pos);
  node_t folder = *(node_t *)&readBuffer;
  int free_position = folder.datablocks_length;
  folder.datablocks[free_position] = new_link;
  folder.datablocks_length += 1;

  // system_write_object(&folder, sizeof(node_t), folder_pos);

}

void system_new_write_folder(int id, char name[16]){
  node_t new_folder;
  memset( &new_folder, 0, sizeof( node_t ) );
  new_folder.s = '('; new_folder.e = ')'; new_folder.parentId = 0;
  new_folder.id = id;
  new_folder.datablocks_length = 0;
  new_folder.type = TYPE_FOLDER;
  strcpy(new_folder.name, name);


  // Temp
  folder_pos = start_node_address;

  // Write Node
  system_write_object(&new_folder, sizeof(node_t), start_node_address);

  // Add to addresses since it is a new write
  start_node_address += (sizeof(node_t) % WRITE_SIZE) ? ((sizeof(node_t) / WRITE_SIZE) + 1) : (sizeof(node_t) / WRITE_SIZE);

}
