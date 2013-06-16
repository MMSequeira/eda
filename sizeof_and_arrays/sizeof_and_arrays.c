// `sizeof_and_arrays.c` &ndash; _Arrays_ e `sizeof`
// ================================================= 

#include <stdio.h>
#include <stdlib.h>

void print(int number_of_items, int items[number_of_items])
{
	printf("sizeof(items): %zu\n", sizeof(items));

	for (int i = 0; i != number_of_items; i++)
		printf("items[%d] = %d\n", i, items[i]);
}

int main(void)
{
	int ages[] = {23, 24, 25, 26};

	printf("sizeof(ages):          %zu\n", sizeof(ages));
	printf("sizeof(char):          %zu\n", sizeof(char));
	printf("sizeof(short int):     %zu\n", sizeof(short int));
	printf("sizeof(int):           %zu\n", sizeof(int));
	printf("sizeof(long int):      %zu\n", sizeof(long int));
	printf("sizeof(long long int): %zu\n", sizeof(long long int));
	print(sizeof(ages) / sizeof(int), ages);

	return EXIT_SUCCESS;
}
