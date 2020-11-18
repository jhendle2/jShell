/* FileManager.c */

#include "FileManager.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../DataStructures/LinkedList.h"

//#include "FileLookupTable.h"


void add_sub_file(FILEPTR parent, FILEPTR sub_file){
	sub_file->parent = parent;
	void* sub_file_as_data = (void*)(sub_file);
	push_back(parent->sub_files_anchor, sub_file_as_data, TYPE_file);
	parent->num_sub_files = num_nodes(parent->sub_files_anchor);
}

void print_file(FILEPTR file, int tab_offset, char tab_str[16]){
	for(int i = 0; i<tab_offset; i++) printf("%s",tab_str);
	
	/*if(file->is_directory){
		printf("DREC %s\n",
			file->name
		);			
	}
	else{
		printf("%s.%s\n",file->name, file->extension);
	}*/
	
	printf("%s.%s\n",file->name, file->extension);

}

void print_directory_and_sub_files(FILEPTR directory){
	print_file(directory,0,"\t");
	print_list_from_index(directory->sub_files_anchor,1);
}

void print_sub_files(FILEPTR directory){
	print_list_from_index(directory->sub_files_anchor,1);
}

FILEPTR find_sub_file(FILEPTR directory, char name[FILE_NAME_LENGTH], char extension[EXTENSION_LENGTH]){
	LinkedList temp = directory->sub_files_anchor;
	
	while(temp!=NULL){
		FILEPTR temp_file = (FILEPTR)(temp->data);
		if(strcmp(temp_file->name,name)==0 &&
			strcmp(temp_file->extension,extension)==0) return temp_file;
		temp = temp->next_node;
	}
	return directory;
}

void file_tree(FILEPTR directory, int level){
	print_file(directory,level," . ");
	FILEPTR temp_file = directory;
	int num_sub_files = temp_file->num_sub_files;
	
	if(temp_file->num_sub_files > 0){
		for(int i = 1; i<=num_sub_files; i++){
			node* temp_node = get_node(temp_file->sub_files_anchor, i);
			FILEPTR file_in_node = (FILEPTR)(temp_node->data);
			file_tree(file_in_node, level+1);
		}
	}else{
		//print_file(temp_file, level);
	}
}