#include "File.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

FILEPTR new_File(char name[FILE_NAME_LENGTH], char extension[EXTENSION_LENGTH]){
		
	FILEPTR out_file = (FILEPTR)malloc(sizeof(File));
	strcpy(out_file->name, name);
	strcpy(out_file->extension, extension);
	out_file->sub_files_anchor = new_node((void*)(out_file),TYPE_file);
	out_file->num_sub_files = 0;
	out_file->is_directory = 0;
	
	return out_file;
}

FILEPTR new_Directory(char name[FILE_NAME_LENGTH]){
	FILEPTR out_directory = new_File(name, "DREC");
	out_directory->is_directory = 1;
	return out_directory;
}

char* File_strprotections(FILEPTR file){
	char* out = (char*)malloc(sizeof(char)*4);
	out[0] = (file->protections[0]) ? 'R' : '.';
	out[1] = (file->protections[0]) ? 'W' : '.';
	out[2] = (file->protections[0]) ? 'X' : '.';
	out[3] = '\0';
	return out;
}