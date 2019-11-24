#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define SIZE 50
#define SHIFT 4

typedef enum {m_void, m_int, m_array} M_TYPE;

typedef struct Entry Entry;

struct Entry {
	char* key;
	Entry* next;		
	
	// Attributes
	M_TYPE type;
	int val;
};

Entry* Table[SIZE];

Entry* make_entry(char* key) {
	Entry* new_entry = (Entry*)malloc(sizeof(Entry));
	
	new_entry->key = key;
	new_entry->next = 0;
	
	// Give the attributes temp vals
	new_entry->type = m_void;
	new_entry->val = 0;

	return new_entry;
}

void set_type(Entry* e, M_TYPE t) {
	e->type = t;	
}

void set_val(Entry* e, int v) {
	e->val = v;
}

void init_table(Entry** table, int size) {
	table = malloc(sizeof(Entry)*size);
}

// Louden
int hash(char* key) {
	int temp = 0;
	int i = 0;
	while (key[i] != '\0') {
		temp = ((temp << SHIFT) + key[i]) % SIZE;
		++i;
	}

	return temp;
}

int lookup(Entry** table, char* key) {
	int target_hash = hash(key);

	// The location is empty
	if (!table[target_hash]) return -1;

	// The location is not empty, traverse it
	int loc = 0;
	Entry* curr = table[target_hash];
	while (curr) {
		if (strcmp(curr->key, key) == 0) {
			return loc;
		}
		curr = curr->next;
		loc++;
	}

	return -1;
}

void insert(Entry** table, char* key) {
	int curr_hash = hash(key);

	printf("inserting %s...\n", key);

	// Already in the table
	if (lookup(table, key) >= 0) return;
	
	if (!table[curr_hash]) {
		table[curr_hash] = make_entry(key);
	} else {
		Entry* curr = table[curr_hash];
		if (curr) {	
			while (curr->next) {
				curr = curr->next;
			}
			curr->next = make_entry(key);
		}
	}
}

// Debug usage
void print(Entry** table, unsigned int size) {
	int i = 0;
	for (i = 0; i < size; i++) {
		Entry* curr = table[i];
		if (curr) {
			printf("%d: %s", i, curr->key);
			while (curr->next) {
				printf(" -> %s", curr->next->key);
				curr = curr->next;
			}
			printf("\n");
		} else {
			printf("%d: \n", i);
		}
	}
}

#endif

