#include "LinkedList.h"
#include "../IOManager/PrintHandler.h"
#include <stdio.h>
#include <stdlib.h>

#include "../FileManager/FileManager.h"
#include "datatypes.h"

LinkedList new_node(DATA_TYPE data, enum TYPE type){
	LinkedList n = (LinkedList)malloc(sizeof(node));
	n->type = type;
	n->data=data;
	return n;
}

int is_empty(LinkedList anchor){
	return (anchor==NULL);
}
int is_full(LinkedList anchor){
	LinkedList n = (LinkedList)malloc(sizeof(node));
	int full_status = (n==NULL);
	if(!full_status) free(n);
	return full_status;
}
int num_nodes(LinkedList anchor){
	int num = 0;
	LinkedList temp = anchor;
	while(temp->next_node!=NULL){
		temp = temp->next_node;
		num++;
	}
	return num;
}

DATA_TYPE front_node(LinkedList anchor){
	return anchor->data;
}
DATA_TYPE back_node(LinkedList anchor){
	LinkedList temp = anchor;
	while(temp->next_node!=NULL){
		temp = temp->next_node;
	}
	return temp->data;
}

void push_front(LinkedList anchor, DATA_TYPE data, enum TYPE type){ // Broken?
	LinkedList second_node = new_node(anchor->data,anchor->type);
	second_node->previous_node = anchor;
	second_node->next_node = anchor->next_node;
	anchor->next_node->previous_node = second_node; // Fixed?
	anchor->next_node = second_node;
	anchor->data = data;
	anchor->type = type;
}
void push_back(LinkedList anchor, DATA_TYPE data, enum TYPE type){
	LinkedList temp = anchor;
	while(temp->next_node!=NULL){
		temp = temp->next_node;
	}
	LinkedList back_node = new_node(data,type);
	temp->next_node = back_node;
	back_node->previous_node = temp;	
}
void insert_before_node(LinkedList anchor, DATA_TYPE data, enum TYPE type, int index){
	int i = 0;
	LinkedList temp = anchor;
	while(temp->next_node!=NULL){
		if(i==index) break;
		temp = temp->next_node;
		i++;
	}
	
	LinkedList previous = temp->previous_node;
	
	LinkedList inserted = new_node(data,type);
	inserted->previous_node = previous;
	previous->next_node = inserted;
	inserted->next_node = temp;
	temp->previous_node = inserted;
}
void set_node(LinkedList anchor, DATA_TYPE data, enum TYPE type, int index){
	int i = 0;
	LinkedList temp = anchor;
	while(temp->next_node!=NULL){
		if(i==index) break;
		temp = temp->next_node;
		i++;
	}
	if(temp!=NULL) temp->data=data;
}

LinkedList get_node(LinkedList anchor, int index){
	int i = 0;
	LinkedList temp = anchor;
	while(temp->next_node!=NULL){
		if(i==index) break;
		temp = temp->next_node;
		i++;
	}
	return temp;
}
LinkedList pop_node(LinkedList anchor, int index){
	int i = 0;
	LinkedList temp = anchor;
	while(temp->next_node!=NULL){
		if(i==index) break;
		temp = temp->next_node;
		i++;
	}
	
	LinkedList previous = temp->previous_node;
	LinkedList next = temp->next_node;
	
	previous->next_node = next;
	next->previous_node = previous;
	
	temp->previous_node = NULL;
	temp->next_node = NULL;
	
	return temp;
}
void delete_node(LinkedList anchor, int index){
	int i = 0;
	LinkedList temp = anchor;
	while(temp->next_node!=NULL){
		if(i==index) break;
		temp = temp->next_node;
		i++;
	}
	
	LinkedList previous = temp->previous_node;
	LinkedList next = temp->next_node;
	
	previous->next_node = next;
	next->previous_node = previous;
	
	free(temp);
}
/*LinkedList find_node(LinkedList anchor, DATA_TYPE data, enum TYPE type){
	LinkedList temp = anchor;
	while(temp!=NULL){
		DATA_TYPE temp_data = temp->data;
		enum TYPE temp_type = temp->type;
		
		if(temp_data==data && temp_type==type) return temp;
		
		temp = temp->next_node;
	}
	return anchor;
}*/

void print_list(LinkedList anchor){
	LinkedList temp = anchor;
	while(temp!=NULL){
		print_from_type(temp->data, temp->type);
		temp = temp->next_node;
	}printf("\n");
}

void print_list_from_index(LinkedList anchor, int index){
	LinkedList gotten_node = get_node(anchor, index);
	print_list(gotten_node);
}