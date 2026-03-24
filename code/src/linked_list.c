#include "linked_list.h"

link_list_uint* add_list_uint(link_list_uint *L, unsigned int x) {
	link_list_uint *new;
	new = (link_list_uint*) malloc(sizeof(*new));
	new->val = x;
	new->next = L;
	return new;
}

link_list_uint* init_list_uint(unsigned int val) {
	link_list_uint *L;
	L = (link_list_uint*) malloc(sizeof(*L));
	L->val = val;
	L->next = NULL;
	return L;
}

void print_list_uint(link_list_uint *L) {
	printf("[");
	while (L != NULL) {
		printf("%u, ", L->val);
		L = L->next;
	}
	printf("\b\b]\n");
}

void free_list_uint(link_list_uint *L) {
	link_list_uint *prochain;
	while (L != NULL) {
		prochain = L->next;
		free(L);
		L = NULL;
		L = prochain;
	}
}
