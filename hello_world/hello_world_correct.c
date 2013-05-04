#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int factorial(const int n)
{
	assert(0 <= n && n <= 12);

	if (n == 0)
		return 1;
	return n * factorial(n - 1);
}

int main(void)
{
	printf("Hello world! Let's calculate the factorial of a number.\n");

	int number;
	while(true) {
		printf("Please enter a non-negative integer "
		       "between 0 and 12: ");
		if (scanf("%d", &number) == 1 && 0 <= number && number <= 12)
			break;
		if (feof(stdin) || ferror(stdin)) {
			fprintf(stderr,
				"Unrecoverable error reading user response. "
				"Exiting.\n");
			return EXIT_FAILURE;
		}
		printf("Invalid response. Try again.\n");
		scanf("%*[^\n]%*1[\n]");
	}

	printf("%d! = %d\n", number, factorial(number));

	return EXIT_SUCCESS;
}
