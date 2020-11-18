#include <stdio.h>
#include "PrintHandler.h"

#include "../DataStructures/LinkedList.h"
#include "../FileManager/FileManager.h"

void print_from_type(void* data, enum TYPE type){
	switch(type){
		case TYPE_file:
			print_file((FILEPTR)(data),1,"");
			break;
		default:
			break;
	}
}