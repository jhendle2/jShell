#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Shell.h"
#include "ShellCommands.h"
#include "Command.h"

#include "../IOManager/Flags.h"
#include "../IOManager/MacroLookupTable.h"

//#include "FileLookupTable.h"

#include "../FileManager/MyFiles.h"

#include "../FileManager/FileManager.h"
#include "../DataStructures/LinkedList.h"

static void generate_random_files(){
	
	FILEPTR file1 = new_File("file1","FILE");
	FILEPTR file2 = new_File("file2","FILE");
	FILEPTR file3 = new_File("file3","FILE");
	FILEPTR file4 = new_File("file4","FILE");
	FILEPTR file5 = new_File("file5","FILE");
	
	FILEPTR directory1 = new_Directory("my_files");
	FILEPTR directory2 = new_Directory("my_documents");
	
	add_sub_file(directory1, file1);
	add_sub_file(directory1, file2);
	add_sub_file(directory1, file3);
	add_sub_file(directory1, file4);
	
	add_sub_file(directory2, file5);
	add_sub_file(directory2, directory1);
	
	add_sub_file(DREC_Home, directory2);
	
	
	/*FILEPTR file1 = new_File("file1","FILE");
	void* address = (void*)(file1);
	printf("Address of file1 = %p\n",address);
	FILEPTR file1b = (FILEPTR)(address);
	printf("File @%p: %s.%s\n",address,file1b->name,file1b->extension);
	*/
	//FLT_dump();
}

void initialize_ENV_variables(){
	ENV_shell_repeat = 0; // Turn off Shell repeats
}

void boot(){
	char* sbm = "\t---- Initializing jShell ----\n\n";
	Shell_bootup_message = sbm;
	printf("%s",Shell_bootup_message);
	
	printf(".... Beginning Boot Sequence .... \n");
	//initialize_FileLookupTable();
	initialize_MyFiles();
	initialize_MacroLookupTable();
	initialize_ENV_variables();

	generate_random_files();
	printf(".... Ending Boot Sequence .... \n\n");
}

void shell_loop(){
	
	boot();
	
	int exit = 0;
	while(!exit){
		char shell_buff[SHELL_BUFFER_LENGTH];
		printf("\\%s>",DREC_Current->name);
		fgets(shell_buff, sizeof(shell_buff), stdin);
		
		exit = !strncmp(shell_buff,"exit",4);
		if(exit) break;
		if(strlen(shell_buff)==0) continue;
		
		token* tokens = (token*)malloc(sizeof(token)*MAX_TOKENS);
		int num_tokens = tokens_from_line(shell_buff, tokens);
		enum ShellCommand sc = get_command(tokens);
		
		if(ENV_shell_repeat){ /* Echo back Shell input */
			print_tokens(tokens, num_tokens);
			printf("\n");
		}
		
		evaluate_command(sc, tokens, num_tokens);
		
	}

}

int tokens_from_line(char line[SHELL_BUFFER_LENGTH], token* tokens){
	char str[TOKEN_LENGTH];
	for(int j = 0; j<TOKEN_LENGTH; j++) str[j] = 0;
	int token_index = 0;
	
	for(int i = 0; i<SHELL_BUFFER_LENGTH; i++){
		char c = line[i];
		if(c==0) break;
		
		if(c=='\n' || c=='\r') continue;
		if(c==' ' || c=='\t'){
			token temp_token;
			
			/* Check if token is a macro & expand */
			/* Don't do this for macro commands */
			if(strcmp(tokens[0].str,"macro")!=0 &&
				MLT_is_macro(str)){
				strcpy(str, MLT_find_and_expand_macro(str));
			}
			strcpy(temp_token.str,str);
			
			tokens[token_index++] = temp_token;
			for(int j = 0; j<TOKEN_LENGTH; j++) str[j] = 0;
		}
		else{
			char chrstr[2];
			chrstr[0] = c; chrstr[1] = 0;
			strncat(str,chrstr,1);
		}
	}
	if(strlen(str)>0){
		token temp_token;
		/* See above */
		if(strcmp(tokens[0].str,"macro")!=0 &&
			MLT_is_macro(str)){
			strcpy(str, MLT_find_and_expand_macro(str));
		}
		strcpy(temp_token.str,str);
		tokens[token_index++] = temp_token;
	}
	
	return token_index;
}

enum ShellCommand get_command(token* tokens){
	if(strcmp(tokens[0].str,		"tree")==0) 	return SC_tree;
	else if(strcmp(tokens[0].str,	"mkdir")==0) 	return SC_mkdir;
	else if(strcmp(tokens[0].str,	"cd")==0)		return SC_cd;
	else if(strcmp(tokens[0].str,	"ls")==0)		return SC_ls;
	else if(strcmp(tokens[0].str,	"env")==0)		return SC_env;
	else if(strcmp(tokens[0].str,	"macro")==0)	return SC_macro;
	else if(strcmp(tokens[0].str,	"echo")==0)		return SC_echo;
	else if(strcmp(tokens[0].str,	"mkfil")==0)	return SC_mkfil;
	else if(strcmp(tokens[0].str,	"lac")==0)	return SC_lac;
	else if(strcmp(tokens[0].str,	"prtc")==0)	return SC_prtc;
	
	return SC_none;
}
void evaluate_command(enum ShellCommand sc, token* tokens, int num_tokens){
	switch(sc){
		case SC_tree:
			exec_tree(tokens, num_tokens);
			printf("\n");
			break;
			
		case SC_mkdir:
			exec_mkdir(tokens, num_tokens);
			break;
			
		case SC_cd:
			exec_cd(tokens, num_tokens);
			break;
		
		case SC_ls:
			exec_ls(tokens, num_tokens);
			printf("\n");
			break;
			
		case SC_env:
			exec_env(tokens, num_tokens);
			break;
						
		case SC_macro:
			exec_macro(tokens, num_tokens);
			break;
			
		case SC_echo:
			exec_echo(tokens, num_tokens);
			break;
			
		case SC_mkfil:
			exec_mkfil(tokens, num_tokens);
			break;
			
		case SC_lac:
			exec_lac();
			printf("\n");
			break;
			
		case SC_prtc:
			exec_prtc(tokens, num_tokens);
			break;
			
		default:
			break;
	}
}

void print_tokens(token* tokens, int num_tokens){
	for(int i = 0; i<num_tokens; i++){
		printf("<%s> ",tokens[i].str);
	}
}