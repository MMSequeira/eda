#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n)
{
	if (n < 2)
		return 1;
	return fibonacci(n - 2) + fibonacci(n - 1);
}

int main()
{
	double previous_time = 0.0;
	for (int n = 0; n != 45; n++) {
		clock_t start = clock();
		int f = fibonacci(n);
		clock_t end = clock();
		double time = (double) (end - start) / CLOCKS_PER_SEC;
		printf("f(%d) = %d in %.4fs %g\n", n, f, time,
			time / previous_time);
		previous_time = time;
	}

    return EXIT_SUCCESS;
}
