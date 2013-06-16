// `command_line.c` &ndash; Processamento da linha de comandos
// ===========================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argument_count, char *argument_values[argument_count])
{
	printf("Number of arguments: '%d'\n", argument_count);
	for (int i = 0; i != argument_count; i++)
		printf("Argument %d: '%s'\n", i, argument_values[i]);

	if (argument_count < 3) {
		fprintf(stderr, "Error: Insuficient number of arguments!\n");
		return EXIT_FAILURE;
	}

	if (strcmp(argument_values[1], "bubble") == 0)
		printf("Bubble sort selected!\n");
	else if (strcmp(argument_values[1], "insertion") == 0)
		printf("Insertion sort selected!\n");
	else {
		fprintf(stderr, "Error! Unknown algorithm '%s'!\n",
			argument_values[1]);
		return EXIT_FAILURE;
	}

	FILE *file = fopen(argument_values[2], "r");

	if (file == NULL) {
		fprintf(stderr, "Could not open file '%s'!\n",
			argument_values[2]);
		return EXIT_FAILURE;
	}

	// Process file....
	printf("Processing file '%s'...\n", argument_values[2]);

	fclose(file);

	return EXIT_SUCCESS;
}












