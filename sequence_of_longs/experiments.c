#include <stdio.h>
#include <stdlib.h>

struct sequence_of_longs {
	long* items;
	int length;
};

void SEQL_println(struct sequence_of_longs *sl)
{
	printf("Length: %d\nItems:", sl->length);
	for (int i = 0; i != sl->length; i++)
		printf(" %ld", sl->items[i]);
	printf("\n");
}

void SEQL_initialize(struct sequence_of_longs *sl)
{
	sl->length = 0;
	sl->items = NULL;
}

int SEQL_length(struct sequence_of_longs *sl)
{
	return sl->length;
}

void SEQL_add(struct sequence_of_longs *sl, long new_item)
{
	sl->items = realloc(sl->items, (sl->length + 1) * sizeof(long));
	sl->items[sl->length++] = new_item;
}

int SEQL_item(struct sequence_of_longs* sl, int index)
{
	return sl->items[index];
}

int main_experiment(void)
{
	struct sequence_of_longs sequence;
	SEQL_initialize(&sequence);

	for (long i = 0L; i != 10L; i++)
		SEQL_add(&sequence, i);

	printf("Length = %d\n", SEQL_length(&sequence));

	SEQL_println(&sequence);

	printf("Itens are: ");
	for (int i = 0; i != SEQL_length(&sequence); i++)
		printf(" %d", SEQL_item(&sequence, i));
	putchar('\n');

	return EXIT_SUCCESS;
}
