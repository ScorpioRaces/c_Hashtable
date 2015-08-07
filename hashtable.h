#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdbool.h>

typedef struct {
	int **buckets;
	int *size_of_buckets, *lengths;
	int numbuck;
} HashTable;

HashTable* hashtable_create(int num_buckets);

void hashtable_destroy(HashTable *h);
//returns true if added
bool hashtable_add(HashTable *h, int x);

void hashtable_print(HashTable *h);
#endif

