#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#define INIT_BSIZE 10

HashTable* hashtable_create(int num_buckets) {
	int **buckets = malloc(num_buckets*sizeof(int*));
	int *size_of_buckets = malloc(num_buckets*sizeof(int)); 
	int *lengths = malloc(num_buckets*sizeof(int));

	int j;
	for(j = 0; j<num_buckets; j++){
		buckets[j] = malloc(INIT_BSIZE*sizeof(int));
		lengths[j] = 0;
		size_of_buckets[j] = INIT_BSIZE;
	}
	HashTable *h = malloc(sizeof(HashTable));
	h->buckets = buckets;
	h->lengths = lengths;
	h->size_of_buckets = size_of_buckets;
	h->numbuck = num_buckets;

	return h;
}

void hashtable_destroy(HashTable *h) {
	int i;
	for(i=0; i<h->numbuck; i++) {
		free(h->buckets[i]);
	}
	free(h->lengths);
	free(h->size_of_buckets);
	free(h->buckets);
	free(h);
}

int hash(int num) {
	return (num*(num+3));
}

bool hashtable_add(HashTable *h, int x) {
	int i;
	int b = hash(x) % h->numbuck;
	for(i = 0; i < h->lengths[b]; i++) { 
		if(h->buckets[b][i] == x) return false;
	}
	//add x to hashtable
	if(h->lengths[b] == h->size_of_buckets[b]) {
		h->size_of_buckets[b] *= 2;
		h->buckets[b] = realloc(h->buckets[b], h->size_of_buckets[b]*sizeof(int));
	}
	h->buckets[b][h->lengths[b]++] = x;
	return true;
}	

void hashtable_print(HashTable *h) {
	int l, k;
	for(l=0; l<h->numbuck; l++) {
		for(k=0; k<h->lengths[l]; k++) {
			printf("%i\n", h->buckets[l][k]);
		}
	}
}

