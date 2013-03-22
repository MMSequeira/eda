#include <stdio.h>
#include <stdlib.h>

int double_of(int n)
{
	return 2 * n;
}

int triple_of(int n)
{
	return 3 * n;
}

//void try_function(int f(int))
void try_function(int (*f)(int))
{
//	printf("f(4) = %d\n", f(4));
	printf("f(4) = %d\n", (*f)(4));
}

int main()
{
	try_function(double_of);
	try_function(triple_of);

	try_function(&double_of);

//	int (*f)(int) = &double_of;
	int (*f)(int) = double_of;
//	int f(int) = double_of; ERROR!

//	int n = (*f)(5);
	int n = f(5);

	printf("n = %d\n", n);

	return EXIT_SUCCESS;
}













