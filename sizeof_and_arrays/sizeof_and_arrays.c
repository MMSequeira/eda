// `sizeof_and_arrays.c` &ndash; _Arrays_ e `sizeof`
// ================================================= 

#include <stdio.h>
#include <stdlib.h>

// Change name to something else.
void print(int number_of_items, int items[number_of_items])
{
	printf("%lu\n", sizeof(items));

	for (int i = 0; i != number_of_items; i++)
		printf("%d\n", items[i]);
}

// Eu: inicialização de arrays de comprimento variável.
// Todos: %d para sizeof é erro.
int main(void)
{
	int ages[] = {23, 24, 25, 26};

	printf("%lu\n", sizeof(ages));
//	printf("%lu\n", sizeof(char));
//	printf("%lu\n", sizeof(short int));
//	printf("%lu\n", sizeof(int));
//	printf("%lu\n", sizeof(long int));
//	printf("%lu\n", sizeof(long long int));

	print(sizeof(ages) / sizeof(int), ages);

	return EXIT_SUCCESS;
}
