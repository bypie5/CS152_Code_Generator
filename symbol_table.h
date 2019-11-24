#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define SIZE 20
#define SHIFT 4

typedef enum {m_void, m_int, m_array} M_TYPE;

typedef struct Entry Entry;

struct Entry {
	char* key;
	Entry* next;		
	M_TYPE type;
};

Entry* Table[SIZE];

Entry* make_entry(char* key) {
	Entry* new_entry = (Entry*)malloc(sizeof(Entry));
	
	new_entry->key = key;
	new_entry->next = 0;
	new_entry->type = ml_void;
	new_entry->mil = 0;
	new_entry->name = 0;

	return new_entry;
}

void set_mil(Entry* e, char* new_mil) {
	e->mil = new_mil;
}

void set_name(Entry* e, char* new_name) {
	e->name = new_name;
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

void insert(Entry** table, char* key) {
	int curr_hash = hash(key);

	// Already in the table
	if (lookup(table, key)) return;
	
	if (!table[curr_hash]) {
		table[curr_hash] = make_entry(key);
	} else {
		Entry* curr = table[curr_hash];
		if (curr) {	
			while (curr->next) {
				curr = curr->next;
			}
			curr->next = malloc(sizeof(Entry*));
			curr->next = make_entry(key);
		}
	}
}

int lookup(Entry** table, char* key) {
	int target_hash = hash(key);

	if (!table[target_hash]) return 0;

	Entry* curr = table[target_hash];
	while (curr) {
		if (strcmp(curr->key, key) == 0) {
			return 1;
		}
		curr = curr->next;
	}

	return 0;
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

