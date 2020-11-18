/* FileManager.h */

#ifndef FILEMANAGER
#define FILEMANAGER

#include <stdint.h>
#include "File.h"

void add_sub_file(FILEPTR parent, FILEPTR sub_file);	

char* list_sub_files(FILEPTR file);

// Testing Stuff
void print_file(FILEPTR file, int tab_offset, char tab_str[16]);
void print_directory_and_sub_files(FILEPTR directory);
void print_sub_files(FILEPTR directory);

FILEPTR find_sub_file(FILEPTR directory, char name[FILE_NAME_LENGTH], char extension[EXTENSION_LENGTH]);

void file_tree(FILEPTR directory, int level);

#endif