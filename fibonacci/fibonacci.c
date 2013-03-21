#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int stupidly_recursive_fibonacci(int n)
{
	if (n < 2)
		return 1;
	return stupidly_recursive_fibonacci(n - 2)
		+ stupidly_recursive_fibonacci(n - 1);
}

int iterative_fibonacci(int n)
{
	if (n == 0 || n == 1)
		return 1;

	int f_i_1 = 1, f_i_2 = 1;
	for(int i = 2; i != n + 1; i++) {
		int f_i = f_i_2 + f_i_1;
		f_i_2 = f_i_1;
		f_i_1 = f_i;
	}

	return f_i_1;
}

int main()
{

	for (int n = 0; n != 10; n++)
		printf("F(%d) = %d\n", n,
			iterative_fibonacci(n));

	return EXIT_SUCCESS;

	double previous_time = 0.0;
	for (int n = 0; n != 45; n++) {
		clock_t start = clock();
		int f = stupidly_recursive_fibonacci(n);
		clock_t end = clock();
		double time = (double) (end - start) / CLOCKS_PER_SEC;
		printf("f(%d) = %d in %.4fs %g\n", n, f, time,
			time / previous_time);
		previous_time = time;
	}

    return EXIT_SUCCESS;
}
