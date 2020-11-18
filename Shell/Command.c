#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Command.h"
#include "Shell.h"

#include "../IOManager/Flags.h"
#include "../IOManager/MacroLookupTable.h"
#include "../FileManager/FileManager.h"
#include "../FileManager/MyFiles.h"
#include "../ErrorHandler/ErrorTable.h"

void exec_lac(){
	/*
	SC_none, // Noop
	SC_tree, // List files in directory as hierarchy tree
	SC_mkdir, // Make a directory
	SC_mkfil, // Make a file
	SC_cd, // List current directory or move to another
	SC_ls, // List all files in a current directory
	SC_env, // Create?, display, or modify an environment variable
	SC_macro, // Create, display, or modify a macro
	SC_echo, // Echo back what was written
	SC_lac // List all commands
	*/
	printf(" . tree - List files in directory as hierarchy tree\n");
	printf(" . mkdir - Make a directory\n");
	printf(" . mkfil - Make a file\n");
	printf(" . cd - List current directory or move to another\n");
	printf(" . ls - List all files in a current directory\n");
	printf(" . env - Create, display, or modify an environment variable\n");
	printf(" . macro - Create, display, or modify a macro\n");
	printf(" . echo - Echo back what was written\n");
	printf(" . lac - List all commands\n");
}

void exec_tree(token* tokens, int num_tokens){
	FILEPTR directory;
	if(DREC_Current!=0) directory = DREC_Current;
	if(num_tokens>1) ; /// TODO: Add this
	file_tree(directory, 0);
}

void exec_mkdir(token* tokens, int num_tokens){
	FILEPTR directory = DREC_Current;
	
	if(num_tokens<2){
		ERROR_not_enough_params();
		return;
	}
	
	FILEPTR new_directory = new_Directory(tokens[1].str);
	add_sub_file(directory, new_directory);
}

static void capitalizeextension(char extension[EXTENSION_LENGTH]){
	char *s = extension;
	while (*s){ // Capitalize extension
		*s = toupper((unsigned char) *s);
		s++;
	}
}

/* So fucking broken it's unreal */
static void str2nameandextension(char** nameandextension, char str[SHELL_BUFFER_LENGTH], char* period_pointer, int period_index){
	//char file_name[FILE_NAME_LENGTH];
	//char extension[EXTENSION_LENGTH];
			
	strncpy(nameandextension[0],str,period_index);
	int end_of_string_index = strlen(str)-period_index;
	strncpy(nameandextension[1],str+period_index+1,end_of_string_index);
	
	capitalizeextension(nameandextension[1]);
}

void exec_mkfil(token* tokens, int num_tokens){
	if(num_tokens<2){
		ERROR_not_enough_params();
		return;
	}
	
	FILEPTR temp_file;
	
	if(num_tokens<3){
		/* Is there a period in token[2].str? */
		char* period_pointer = strchr(tokens[1].str, '.');
		int period_index = period_pointer - tokens[1].str;
		if(period_pointer!=NULL){
			//char file_name[FILE_NAME_LENGTH];
			//char extension[EXTENSION_LENGTH];
			
			char** nameandextension = (char**)malloc(sizeof(char)*FILE_NAME_LENGTH+sizeof(char)*EXTENSION_LENGTH);
			str2nameandextension(nameandextension, tokens[1].str, period_pointer, period_index);
			
			temp_file = new_File(nameandextension[0],nameandextension[1]);
		}
		/* There isn't */
		else{
			printf("!! ERROR: missing extension for file\n");
			printf(" ? Set one with> mkfil FILE EXTENSION\n");
			return;
		}
		
	}
	else temp_file = new_File(tokens[1].str,tokens[2].str);
	
	add_sub_file(DREC_Current, temp_file);
}

void exec_cd(token* tokens, int num_tokens){
	FILEPTR last_directory = DREC_Current;
		
	if(num_tokens<2){
		print_file(last_directory,0,"");
		return;
	}
	
	if(strcmp(tokens[1].str,"HOME")==0) // Go home
		DREC_Current = DREC_Home;
	else if(strcmp(tokens[1].str,"..")==0){ // Go up
		if(DREC_Current!=DREC_Home)
			DREC_Current = DREC_Current->parent;
	}
	else{
		DREC_Current = find_sub_file(DREC_Current, tokens[1].str, "DREC");
		if(last_directory!=DREC_Current)
			printf("\tCD moved to: %s\n",DREC_Current->name);
	}
}

void exec_ls(token* tokens, int num_tokens){
	FILEPTR directory = DREC_Current;
	
	// Hard coding this shit b/c fuck the PrintHandler oh my god
	LinkedList sub_files_anchor = directory->sub_files_anchor->next_node;
	while(sub_files_anchor!=NULL){
		FILEPTR temp_file = (FILEPTR)(sub_files_anchor->data);
		printf(" . %s.%s\n",temp_file->name,temp_file->extension);
		sub_files_anchor = sub_files_anchor->next_node;
	}
	//print_sub_files(directory);
}

/// TODO: Fix this shit - Not reassigning ENV values?
void exec_env(token* tokens, int num_tokens){
	if(num_tokens<2){
		ERROR_not_enough_params();
		return;
	}
	
	int* ENV_to_change; // Set ENV variable (from lookup table?)
	if(strcmp(tokens[1].str,"SHLREP"))
		ENV_to_change = &ENV_shell_repeat;
	
	if(num_tokens>2){ // Change the ENV variable
		char *ptr;
		int new_val = strtol(tokens[2].str, &ptr, 10);
		ENV_to_change = &new_val;
	}
	
	printf("!!SHLREP: %d\n",ENV_shell_repeat);
	printf("\tENV %s = %d\n",tokens[1].str,*ENV_to_change);
}

void exec_macro(token* tokens, int num_tokens){
	if(num_tokens<2){
		ERROR_not_enough_params();
		return;
	}
	
	macroElement me;
	if(MLT_is_macro(tokens[1].str)){ // We found a macro
		me = MLT_find_macro(tokens[1].str);
		
		if(num_tokens>2){
			MLT_modify_macro(me,tokens[2].str);
		}
	}
	else{ // We didn't
		if(num_tokens<3){ // They give a new macro name but no value
			ERROR_macro_lacking_output();
			return;
		}
		else{
			me = new_Macro(tokens[1].str,tokens[2].str);
			MLT_add_macro_from_macro(me);
		}
	}
	
	printf("MACRO %s -> %s\n",me->input,me->output);
}

void exec_echo(token* tokens, int num_tokens){
	if(num_tokens<2) return;
	for(int i = 1; i<num_tokens; i++){
		printf("%s ",tokens[i].str);
	}
	printf("\n");
}

void exec_prtc(token* tokens, int num_tokens){
	FILEPTR last_directory = DREC_Current;
		
	if(num_tokens<2){
		printf("!! ERROR: No input file to modify protections\n");
		return;
	}
	
	FILEPTR temp_file = DREC_Current;
	char* period_pointer = strchr(tokens[1].str, '.');
	int period_index = period_pointer - tokens[1].str;
	if(period_pointer!=NULL){
		char** nameandextension = (char**)malloc(sizeof(char)*FILE_NAME_LENGTH+sizeof(char)*EXTENSION_LENGTH);
		str2nameandextension(nameandextension, tokens[1].str, period_pointer, period_index);
			
		temp_file = find_sub_file(DREC_Current,nameandextension[0],nameandextension[1]);
	}
	if(last_directory!=DREC_Current)
		printf(" %s.%s : %s\n",temp_file->name,temp_file->extension,File_strprotections(temp_file));
}