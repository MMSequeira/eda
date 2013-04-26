#include "sequence_of_longs.h"

#include <stdio.h>
#include <stdlib.h>

struct sequence_of_longs {
	long *items;
	int length;
	int capacity;
};

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

struct sequence_of_longs *SEQL_new(void)
{
	struct sequence_of_longs *sl = malloc(sizeof(struct sequence_of_longs));
	sl->length = 0;
	sl->capacity = 1;
	sl->items = malloc(sl->capacity * sizeof(long));
	return sl;
}

int SEQL_length(struct sequence_of_longs *sl)
{
	return sl->length;
}

void SEQL_add(struct sequence_of_longs *sl, long new_item)
{
	if (sl->length == sl->capacity)
		sl->items = realloc(sl->items,
				    (sl->capacity *= 2) * sizeof(long));
//	if (sl->length == sl->capacity) {
//		long *new_array = malloc((sl->capacity *= 2) * sizeof(long));
//		for (int i = 0; i != sl->length; i++)
//			new_array[i] = sl->items[i];
//		free(sl->items);
//		sl->items = new_array;
//	}

	sl->items[sl->length++] = new_item;
//	sl->items[sl->length] = new_item;
//	sl->length++;
}

long SEQL_item(struct sequence_of_longs *sl, int index)
{
	return sl->items[index];
}

