#include <time.h>
#include <stdio.h>
#include <stdlib.h>

long stupidly_recursive_fibonacci(int n)
{
	if (n < 2)
		return 1L;
	return stupidly_recursive_fibonacci(n - 2)
		+ stupidly_recursive_fibonacci(n - 1);
}

long iterative_fibonacci(int n)
{
	if (n == 0 || n == 1)
		return 1L;

	long f_i_1 = 1, f_i_2 = 1;
	for(int i = 2; i != n + 1; i++) {
		long f_i = f_i_2 + f_i_1;
		f_i_2 = f_i_1;
		f_i_1 = f_i;
	}

	return f_i_1;
}

void experiment_efficiency_of(char title[], long fibonacci(int),
			int last_term)
{
	printf("%s\n", title);
	double previous_time = 0.0;
	for (int n = 0; n != last_term + 1; n++) {
		clock_t start = clock();
		int f = fibonacci(n);
		clock_t end = clock();
		double time = (double) (end - start) / CLOCKS_PER_SEC;
		printf("f(%d) = %d in %.4fs %g\n", n, f, time,
			time / previous_time);
		previous_time = time;
	}
}

int main()
{
//
//	for (int n = 0; n != 10; n++)
//		printf("F(%d) = %d\n", n,
//			iterative_fibonacci(n));
//
//	return EXIT_SUCCESS;

	experiment_efficiency_of("Stupidly recursive implementation of the fibonacci sequence:",
				stupidly_recursive_fibonacci, 35);
	experiment_efficiency_of("Three variable iterative implementation of the fibonacci sequence:",
				iterative_fibonacci, 1000);

	return EXIT_SUCCESS;
}
