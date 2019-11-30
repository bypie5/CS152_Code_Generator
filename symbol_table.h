#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define T_SIZE 10
#define T_SHIFT 4

// Attributes
typedef enum {m_void, m_int, m_array, m_bool} M_TYPE;
typedef struct Entry Entry;
Entry* Table[T_SIZE];

struct Entry {
	Entry* next;		
	
	// Attributes
	char* key;
	M_TYPE type;
	double i_const_val; // Only valid if type == m_int
	int arr_size; // Only valid if type == m_array
};

// Function declarations
void print();

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

		case m_bool:
			return "m_bool";
			break;

		default:
			return "NO STRING CONVERSION";
			break;
	}
}

Entry* make_entry(char* key) {
	Entry* new_entry = (Entry*)malloc(sizeof(Entry));
	
	new_entry->key = key;
	new_entry->next = 0;
	new_entry->type = m_void;
	new_entry->i_const_val = 0;
	new_entry->arr_size = 0;

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

// Does the entry exist? This function gives the answer
int lookup(char* key) {
	int target_hash = hash(key);

	// The location is empty
	if (!Table[target_hash]) return 0;

	// The location is not empty, traverse i
	Entry* curr = Table[target_hash];
	while (curr) {
		if (strcmp(curr->key, key) == 0) 
			return 1;
		curr = curr->next;
	}

	return 0;
}

Entry* fetch(char* key) {
	// Key is not found in the symbol table
	if (!lookup(key))
		return 0;

	int target_hash = hash(key);
	// Traverse the hash list
	Entry* curr = Table[target_hash];
	while (curr) {
		if (strcmp(curr->key, key) == 0)
			return curr;
		curr = curr->next;
	}

	printf("Something is really wrong with fetch\n");
	return 0;
}

int insert(char* key, M_TYPE t) {
	int curr_hash = hash(key);

	// Already in the table
	if (lookup(key)) return 0;

	if (!Table[curr_hash]) {
		Table[curr_hash] = make_entry(key);
		Table[curr_hash]->type = t;
	} else {
		Entry* curr = Table[curr_hash];
		if (curr) {
			while (curr->next) {
				curr = curr->next;
			}
			curr->next = make_entry(key);
			curr->next->type = t;
		}
	}

	return 1;
}

/* 
 * Attribute modification functions
*/
void set_attr_type(char* key, M_TYPE t) {
	Entry* to_modify = fetch(key);
	if (to_modify != 0) {
		to_modify->type = t;
	}
}

void set_attr_i_const_val(char* key, double d) {
	Entry* to_modify = fetch(key);
	if (to_modify != 0) {
		to_modify->i_const_val = d;
	}
}

void set_attr_arr_size(char* key, int s) {
	Entry* to_modify = fetch(key);
	if (to_modify != 0) {
		to_modify->arr_size = s;
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

