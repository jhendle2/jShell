#ifndef MACROLOOKUPTABLE
#define MACROLOOKUPTABLE

#include "../DataStructures/LinkedList.h"

#define MACRO_INPUT_LENGTH 16
#define MACRO_OUTPUT_LENGTH 128

typedef struct macro_struct{
	char input[MACRO_INPUT_LENGTH];
	char output[MACRO_OUTPUT_LENGTH];
} macro_struct;

typedef macro_struct* macroElement;

macroElement new_Macro(char input[MACRO_INPUT_LENGTH], char output[MACRO_OUTPUT_LENGTH]);

void initialize_MacroLookupTable();

void MLT_add_macro(char input[MACRO_INPUT_LENGTH], char output[MACRO_OUTPUT_LENGTH]);
void MLT_add_macro_from_macro(macroElement macro_temp);
void MLT_remove_macro(char input[MACRO_INPUT_LENGTH]);
void MLT_modify_macro(macroElement macro_temp, char output[MACRO_OUTPUT_LENGTH]);
macroElement MLT_find_macro(char input[MACRO_INPUT_LENGTH]);
char* MLT_expand_macro(macroElement macro);
char* MLT_find_and_expand_macro(char input[MACRO_INPUT_LENGTH]);
void MLT_clear_all_macros();

int MLT_is_macro(char input[MACRO_INPUT_LENGTH]);

#endif