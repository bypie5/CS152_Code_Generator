#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define T_SIZE 25
#define T_SHIFT 4

// Attributes
typedef enum {m_void, m_int, m_array} M_TYPE;
typedef struct Entry Entry;
Entry* Table[T_SIZE];

char* M_TYPE_To_String(M_TYPE t) {
	switch (t)
	{
		case m_void:
			return "m_void";
			break;
		
		case m_int:
			return "m_int";
			break;

		case m_array:
			return "m_array";
			break;

		default:
			return "NO STRING CONVERSION";
			break;
	}
}

struct Entry {
	char* key;
	Entry* next;		
	
	// Attributes
	M_TYPE type;
	char* val;
};

Entry* make_entry(char* key, M_TYPE t) {
	Entry* new_entry = (Entry*)malloc(sizeof(Entry));
	
	new_entry->key = key;
	new_entry->next = 0;
	
	// Give the attributes temp vals
	new_entry->type = t;
	new_entry->val = 0;

	return new_entry;
}

// Louden
int hash(char* key) {
	int temp = 0;
	int i = 0;
	while (key[i] != '\0') {
		temp = ((temp << T_SHIFT) + key[i]) % T_SIZE;
		++i;
	}

	return temp;
}

int lookup(char* key) {
	int target_hash = hash(key);

	// The location is empty
	if (!Table[target_hash]) return -1;

	// The location is not empty, traverse it
	int loc = 0;
	Entry* curr = Table[target_hash];
	while (curr) {
		if (strcmp(curr->key, key) == 0) {
			return loc;
		}
		curr = curr->next;
		loc++;
	}

	return -1;
}

void insert(char* key, M_TYPE t) {
	int curr_hash = hash(key);

	printf("inserting %s...\n", key);

	// Already in the table
	if (lookup(key) >= 0) return;

	if (!Table[curr_hash]) {
		Table[curr_hash] = make_entry(key, t);
	} else {
		Entry* curr = Table[curr_hash];
		if (curr) {
			while (curr->next) {
				curr = curr->next;
			}
			curr->next = make_entry(key, t);
		}
	}
}

// Debug usage
void print() {
	int i = 0;
	for (i = 0; i < T_SIZE; i++) {
		Entry* curr = Table[i];
		if (curr) {
			printf("%d: %s (%s)", i, curr->key, M_TYPE_To_String(curr->type));
			while (curr->next) {
				printf(" -> %s (%s)", curr->next->key,  M_TYPE_To_String(curr->next->type));
				curr = curr->next;
			}
			printf("\n");
		} else {
			printf("%d: \n", i);
		}
	}
}

#endif

