#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct link_list_tab64 {
	uint64_t *val;
	int size;
	struct link_list_64 *next;
}link_list_64;


typedef struct link_list_uint {
	int val;
	struct link_list_uint *next;
}link_list_uint;

#endif
