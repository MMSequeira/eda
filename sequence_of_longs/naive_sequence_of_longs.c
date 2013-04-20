#include "naive_sequence_of_longs.h"

#include <stdio.h>
#include <stdlib.h>

void NSEQL_print(struct naive_sequence_of_longs *sl)
{
	putchar('{');
	for (int i = 0; i != sl->length; i++) {
		if (i != 0)
			printf(", ");
		printf("%ld", sl->items[i]);
	}
	putchar('}');
}

void NSEQL_println(struct naive_sequence_of_longs *sl)
{
	NSEQL_print(sl);
	putchar('\n');
}

void NSEQL_initialize(struct naive_sequence_of_longs *sl)
{
	sl->length = 0;
	sl->items = NULL;
}

int NSEQL_length(struct naive_sequence_of_longs *sl)
{
	return sl->length;
}

void NSEQL_add(struct naive_sequence_of_longs *sl, long new_item)
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

long NSEQL_item(struct naive_sequence_of_longs *sl, int index)
{
	return sl->items[index];
}


