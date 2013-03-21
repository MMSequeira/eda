#include <stdio.h>

void print(int number_of_items, int items[number_of_items])
{
	for (int i = 0; i != number_of_items; i++)
		printf("%d\n", items[i]);
}
