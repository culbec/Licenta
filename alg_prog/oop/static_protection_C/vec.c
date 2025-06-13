#include <stdio.h>
#include <stdlib.h>

// array
static int* e = NULL;
// size of array
static int d = 0;

void destroy();

void init(int *a, int da) {
	if (e != NULL) {
		destroy();
	}

	d = da;
	e = (int*) malloc(d * sizeof(int));

	for (int i = 0; i < d; i++) {
		e[i] = a[i];
	}
}

void destroy() {
	free(e);
	e = NULL;
	d = 0;
}

void squared() {
	if (e == NULL) {
		return;
	}

	for (int i = 0; i < d; i++) {
		e[i] *= e[i];
	}
}

void print() {
	if (e == NULL) {
		return;
	}

	for (int i = 0; i < d; i++) {
		printf("%d ", e[i]);
	}
	printf("\n");
}
