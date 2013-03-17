#include <stdio.h>
#include <stdlib.h>

int factorial(const int n)
{
	if (n == 0)
		return 1;
	return n * factorial(n - 1);
}

int main2(void)
{
	printf("Hello world! Let's calculate the factorial of a number.\n");

	printf("Please enter a non-negative integer: ");

	int number;

	scanf("%d", &number);

	printf("%d! = %d\n", number, factorial(number));

	return EXIT_SUCCESS;
}
