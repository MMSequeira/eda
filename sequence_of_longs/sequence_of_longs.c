#include "sequence_of_longs.h"

#include <stdio.h>
#include <stdlib.h>

void SEQL_print(struct sequence_of_longs *sl)
{
	putchar('{');
	for (int i = 0; i != sl->length; i++) {
		if (i != 0)
			printf(", ");
		printf("%ld", sl->items[i]);
	}
	putchar('}');
}

void SEQL_println(struct sequence_of_longs *sl)
{
	SEQL_print(sl);
	putchar('\n');
}

void SEQL_initialize(struct sequence_of_longs *sl)
{
	sl->length = 0;
	sl->capacity = capacity_increments;
	sl->items = NULL;
}

int SEQL_length(struct sequence_of_longs *sl)
{
	return sl->length;
}

void SEQL_add(struct sequence_of_longs *sl, long new_item)
{
//	sl->items = realloc(sl->items, (sl->length + 1) * sizeof(long));
	long *new_array = malloc((sl->length + 1) * sizeof(long));
	for (int i = 0; i != sl->length; i++)
		new_array[i] = sl->items[i];
	free(sl->items);
	sl->items = new_array;

//	sl->items[sl->length++] = new_item;
	sl->items[sl->length] = new_item;
	sl->length++;
}

long SEQL_item(struct sequence_of_longs *sl, int index)
{
	return sl->items[index];
}

