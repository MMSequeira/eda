#include <stdio.h>
#include <stdlib.h>

int main()
{
//	int n = 1 / 0;

	printf("1.0 / 0.0 = %g\n", 1.0 / 0.0);
	printf("1.0 / -0.0 = %g\n", 1.0 / -0.0);
	printf("0.0 / 0.0 = %g\n", 0.0 / -0.0);

	return EXIT_SUCCESS;
}
