#ifndef LINKEDLIST
#define LINKEDLIST

#define DATA_TYPE void*
#include "datatypes.h"

typedef struct node{
	DATA_TYPE data;
	
	enum TYPE type;
	struct node* previous_node;
	struct node* next_node;
} node;

typedef node* LinkedList;

LinkedList new_node(DATA_TYPE data, enum TYPE type);

int is_empty(LinkedList anchor);
int is_full(LinkedList anchor);
int num_nodes(LinkedList anchor);

DATA_TYPE front_node(LinkedList anchor);
DATA_TYPE back_node(LinkedList anchor);

void push_front(LinkedList anchor, DATA_TYPE data, enum TYPE type);
void push_back(LinkedList anchor, DATA_TYPE data, enum TYPE type);
void insert_before_node(LinkedList anchor, DATA_TYPE data, enum TYPE type, int index);
void set_node(LinkedList anchor, DATA_TYPE data, enum TYPE type, int index);

LinkedList get_node(LinkedList anchor, int index);
LinkedList pop_node(LinkedList anchor, int index);
void delete_node(LinkedList anchor, int index);
//LinkedList find_node(LinkedList anchor, DATA_TYPE data, enum TYPE type);

void print_list(LinkedList anchor);
void print_list_from_index(LinkedList anchor, int index);

#endif