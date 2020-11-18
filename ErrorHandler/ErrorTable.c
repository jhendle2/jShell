#include <stdio.h>

void ERROR_not_enough_params(){
	printf("!! ERROR: Not enough parameters for this command\n");
}

void ERROR_file_not_found(){
	printf("!! ERROR: Couldn\'t find file\n");
}

void ERROR_file_not_in_lookup_table(){
	printf("!! ERROR: File does not exist in FileLookupTable\n");	
}

void ERROR_cannot_expand_macro(){
	printf("!! ERROR: Macro does not exist\n");
	printf(" ? Create it with> macro INPUT OUTPUT\n");
}
void ERROR_macro_lacking_output(){
	printf("!! ERROR: Macro lacks an output\n");
	printf(" ? Set one with> macro INPUT OUTPUT\n");	
}

void ERROR_no_env_variable(){
	printf("!! ERROR: No such Environment Variable\n");
	printf(" ? Create one with> envc NAME VALUE\n");
}

void ERROR_dup_env_variable(){
	printf("!! ERROR: Environment variable with that name already in use\n");
}