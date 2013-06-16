// `malloc_stuff.c` &ndash; Memória dinâmica
// =========================================

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int array_size = 3;
	double *grades = malloc(array_size * sizeof(double));
	*grades = 11.5;
	*(grades + 1) = 33.5;
	// x[y] => *(x + y)
	//*(grades + 2) = -1;
	grades[2] = -1;

	printf("%p\n", grades);

	for (int i = 0; i != array_size; i++)
		printf(" %g", grades[i]);
	putchar('\n');
	// printf("%g\n", *grades);
	// printf("%g\n", *(grades + 1));
	// printf("%g\n", grades[2]);

	grades = realloc(grades, ++array_size * sizeof(double));

	grades[3] = 101.1;

	for (int i = 0; i != array_size; i++)
		printf(" %g", grades[i]);
	putchar('\n');

	double *new_grades = malloc((array_size + 1) * sizeof(double));

	for (int i = 0; i != array_size; i++)
		new_grades[i] = grades[i];

	array_size++;

	free(grades);

	grades = new_grades;

	for (int i = 0; i != array_size; i++)
		printf(" %g", grades[i]);
	putchar('\n');

	free(grades);

	return EXIT_SUCCESS;
}
