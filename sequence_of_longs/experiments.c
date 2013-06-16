// `experiments.c` &ndash; Experiências com sucessões de `long`
// ============================================================

#include <stdio.h>
#include <stdlib.h>

#include "sequence_of_longs.h"
#include "naive_sequence_of_longs.h"

int main(void)
{
	struct sequence_of_longs *sequence = SEQL_new();

	for (long i = 0L; i != 1000L; i++)
		SEQL_add(sequence, i);

	printf("The length is: %d\n", SEQL_length(sequence));

	printf("The sequence is: ");
	SEQL_println(sequence);

	printf("The items are:");
	for (int i = 0; i != SEQL_length(sequence); i++)
		printf(" %ld", SEQL_term(sequence, i));
	putchar('\n');

	free(sequence);

	struct naive_sequence_of_longs *naive_sequence = NSEQL_new();

	for (long i = 0L; i != 1000L; i++)
		NSEQL_add(naive_sequence, i);

	printf("The length (naive) is: %d\n", NSEQL_length(naive_sequence));

	printf("The sequence (naive) is: ");
	NSEQL_println(naive_sequence);

	printf("The items (naive) are:");
	for (int i = 0; i != NSEQL_length(naive_sequence); i++)
		printf(" %ld", NSEQL_term(naive_sequence, i));
	putchar('\n');

	free(naive_sequence);

	return EXIT_SUCCESS;
}
