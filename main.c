#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"

void out_of_memory() {
	fprintf(stderr, "Out of memory\n");
	exit(-1);
}

void file_error(const char *path) {
	fprintf(stderr, "Can't read your file %s\n", path);
	exit(-1);
}

size_t read_line(char **buf, size_t *buflen, const char *path_descriptor, FILE *fh) {
	size_t length = 0;
	while(fgets(*buf+length, *buflen-length, fh) != NULL) {
		length += strlen(*buf+length);
		if(*(*buf+length-1) == '\n') return length;
		*buflen *= 2;
		*buf = realloc(*buf, *buflen*sizeof(char));
		if(*buf == NULL) out_of_memory();
	}
	if(ferror(fh)) file_error(path_descriptor);
	return length;
}

//hash function: h(k) = k(k+3) mod m
int main(int argc, char **argv){
	if(argc != 3) {
		fprintf(stderr, "usage: %s <file> <number of buckets>\n", argv[0]);
		exit(-1);
	}
	int numbuck = atoi(argv[2]);
	FILE *fh = fopen(argv[1], "r");
	if(fh == NULL) file_error(argv[1]);

	HashTable *h = hashtable_create(numbuck);

	size_t buflen = 2;
	char *buf = malloc(buflen*sizeof(char));
	while(read_line(&buf, &buflen, argv[1], fh)) {
		int a = atoi(buf);
		hashtable_add(h, a);	
	}
	hashtable_print(h);
	hashtable_destroy(h);

	fclose(fh);
	return EXIT_SUCCESS;
}