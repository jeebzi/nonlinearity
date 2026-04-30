#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "../include/include.h"

typedef struct link_list_tab64 {
	uint64_t *val;
	int size;
	struct link_list_64 *next;
}link_list_64;


typedef struct link_list_uint {
	int val;
	struct link_list_uint *next;
}link_list_uint;

link_list_uint* add_list_uint(link_list_uint *L, unsigned int x);
link_list_uint* init_list_uint(unsigned int val);
void print_list_uint(link_list_uint *L);
void free_list_uint(link_list_uint *L);


#endif
