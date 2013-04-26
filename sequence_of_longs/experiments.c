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
		printf(" %ld", SEQL_item(sequence, i));
	putchar('\n');

	free(sequence);

	return EXIT_SUCCESS;
}
