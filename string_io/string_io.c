// `string_io.c` &ndash; Saídas sobre cadeias de caracteres
// ========================================================

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	const char *types[] = {
		"sorted",
		"partially_sorted",
		"shuffled",
	};
	const int number_of_types =
		sizeof(types) / sizeof(const char*);

	for (int size = 2; size != 1 << 21; size *= 2)
		for (int i = 0; i != number_of_types; i++) {
			char filename[FILENAME_MAX];
			snprintf(filename, FILENAME_MAX,
				"%s_%d.txt",
				types[i], size);

			printf("The file name is: '%s'\n", filename);
		}

	return EXIT_SUCCESS;
}
