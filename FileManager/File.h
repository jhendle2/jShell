#ifndef FILE_H
#define FILE_H

#include <stdint.h>

#define FILE_NAME_LENGTH 32
#define EXTENSION_LENGTH 8

#include "../DataStructures/LinkedList.h"

struct File{
	uint8_t num_sub_files;
	uint8_t is_visible;
	uint8_t length;
	uint8_t is_directory;
	
	char protections[3]; // READ WRITE EXECUTE	
	char name[FILE_NAME_LENGTH];
	char extension[EXTENSION_LENGTH];
	
	struct File* parent;
	
	LinkedList sub_files_anchor;
} File;

typedef struct File* FILEPTR;

FILEPTR new_File(char name[FILE_NAME_LENGTH], char extension[EXTENSION_LENGTH]);
FILEPTR new_Directory(char name[FILE_NAME_LENGTH]);

char* File_strprotections(FILEPTR file);
#endif