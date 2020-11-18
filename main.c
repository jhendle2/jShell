#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Shell/Shell.h"
#include "IOManager/MacroLookupTable.h"

int main(){
	shell_loop();
	/*
	initialize_MacroLookupTable();
	MLT_add_macro("@","BigBooty");
	char macstr[16];
	strcpy(macstr,MLT_find_and_expand_macro("@"));
	printf("macro expanded: %s\n",macstr);
	printf("is <@> a macro: %d\n",MLT_is_macro("@"));
	printf("is <$> a macro: %d\n",MLT_is_macro("$"));
	*/
	return 0;
}