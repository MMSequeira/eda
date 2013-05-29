#include <stdio.h>
#include <stdlib.h>

int sum(int first, int second)
{
	return first + second;
}

int subtraction(int first, int second)
{
	return first - second;
}

int product(int first, int second)
{
	return first * second;
}

int division(int first, int second)
{
	return first / second;
}

int (*const operations[])(int, int) = {
	sum,
	subtraction,
	product,
	division
};
const int number_of_operations =
	sizeof(operations) /
	sizeof(int (*)(int, int));

int main(void)
{
	for (int i = 0; i != number_of_operations; i++)
		printf("Operation %d: %d\n", i,
			operations[i](5, 2));

	return EXIT_SUCCESS;
}
