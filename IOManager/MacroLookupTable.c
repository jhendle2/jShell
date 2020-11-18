#include "../DataStructures/LinkedList.h"
#include "../DataStructures/datatypes.h"
#include "MacroLookupTable.h"
#include <string.h>
#include <stdlib.h>

LinkedList MacroLookupTable;
macroElement macro_Null;

macroElement new_Macro(char input[MACRO_INPUT_LENGTH], char output[MACRO_OUTPUT_LENGTH]){
	macroElement macro_temp = (macroElement)malloc(sizeof(macro_struct));
	strcpy(macro_temp->input,input);
	strcpy(macro_temp->output,output);
	return macro_temp;
}

void initialize_MacroLookupTable(){
	macroElement macro_HomeDREC = new_Macro("*","HOME");
	//macroElement macro_Null = new_Macro("??????","??????");
	MacroLookupTable = new_node( (void*)(macro_HomeDREC), TYPE_macro);
}

void MLT_add_macro_from_macro(macroElement macro_temp){
	push_back(MacroLookupTable, (void*)(macro_temp), TYPE_macro);
}
void MLT_add_macro(char input[MACRO_INPUT_LENGTH], char output[MACRO_OUTPUT_LENGTH]){
	macroElement macro_temp = new_Macro(input,output);
	push_back(MacroLookupTable, (void*)(macro_temp), TYPE_macro);
}
void MLT_remove_macro(char input[MACRO_INPUT_LENGTH]){
	; /// TODO: This
}
void MLT_modify_macro(macroElement macro_temp, char output[MACRO_OUTPUT_LENGTH]){
	strcpy(macro_temp->output,output);
}
macroElement MLT_find_macro(char input[MACRO_INPUT_LENGTH]){
	LinkedList temp = MacroLookupTable;
	while(temp!=NULL){
		macroElement macro = (macroElement)(temp->data);
		if(strcmp(macro->input,input)==0) return macro;
		temp = temp->next_node;
	}
	return macro_Null;
}
char* MLT_expand_macro(macroElement macro){
	char* out = (char*)malloc(sizeof(char)*strlen(macro->output));
	strcpy(out,macro->output);
	return out;
}
char* MLT_find_and_expand_macro(char input[MACRO_INPUT_LENGTH]){
	macroElement me = MLT_find_macro(input);
	return MLT_expand_macro(me);
}
void MLT_clear_all_macros(){
	;
}
int MLT_is_macro(char input[MACRO_INPUT_LENGTH]){
	return (MLT_find_macro(input)!=macro_Null);
}
