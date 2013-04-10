#include <stdio.h>
#include <stdlib.h>

struct sequence_of_longs {
	long* items;
	int length;
};

void SEQL_println(struct sequence_of_longs *sl)
{
	// TODO SEQL_println is a stub.
//	printf("%d %p %ld\n", s.length, s.items, *s.items);
	printf("Length: %d\nItems:", sl->length);
	for (int i = 0; i != sl->length; i++)
		printf(" %ld", sl->items[i]);
	printf("\n");
}

void SEQL_initialize(struct sequence_of_longs *sl)
{
//	(*sl).length = 0;
//	(*sl).items = NULL;
	sl->length = 0;
	sl->items = NULL;
}

int SEQL_length(struct sequence_of_longs *sl)
{
	return sl->length;
}

void SEQL_add(struct sequence_of_longs *sl, long new_item)
{
	//free(sl->items);
//	sl->items = malloc((sl->length + 1) * sizeof(long));
	sl->items = realloc(sl->items, (sl->length + 1) * sizeof(long));
	sl->items[sl->length++] = new_item;
	//sl->length++;
}

int main(void)
{
	struct sequence_of_longs sequence;
//	struct sequence_of_longs sequence = {};
//	struct sequence_of_longs sequence = {
//		items: NULL,
//		length: 0
//	};
	SEQL_initialize(&sequence);
	for (long i = 0L; i != 10L; i++)
		SEQL_add(&sequence, i);
	printf("Length = %d\n", SEQL_length(&sequence));
	SEQL_println(&sequence);

	return EXIT_SUCCESS;
}
