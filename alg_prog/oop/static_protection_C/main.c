extern void init(int*, int);
extern void destroy();
extern void squared();
extern void print();
extern int* e; // cannot reference, static redeclartion elsewhere and cannot be referenced here

int main() {
	int x[5] = {1, 2, 3, 4, 5};
	init(x, 5);
	squared();
	print();
	destroy();

	int y[] = {1, 2, 3, 4, 5, 6};
	init(y, 6);
	e[1] = 10; // ### ERROR! e is statically protected, can only be referenced from where it is statically declared
	squared();
	print();
	destroy();

	return 0;
}
