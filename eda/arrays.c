#include <stdio.h>
#include <stdlib.h>

double average_of(int number_of_items, int items[number_of_items])
//double average_of(int* items)
{
	double sum = 0.0;

	for (int i = 0; i != number_of_items; i++)
		sum += items[i];

	return sum / 4;
}

// Declare the procedure print which is defined in another file:
void print(int number_of_items, int items[number_of_items]);

int main_arrays(void)
{
//	printf("How many students? ");
//	int number_of_students;
//	scanf("%d", &number_of_students);
//
//	int student_ages[number_of_students];
	int student_ages[] = {23, 24, 25, 26};
	const int number_of_students =
		sizeof(student_ages) / sizeof(int);

	print(number_of_students, student_ages);

	for (int i = 0; i != number_of_students; i++)
		printf("%d\n", student_ages[i]);

	printf("The average age is %g.\n",
		average_of(number_of_students, student_ages));

	return EXIT_SUCCESS;
}
