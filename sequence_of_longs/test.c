#include <stdio.h>
#include <stdlib.h>

struct sequence_of_longs {
	long* items;
	int length;
};

void SEQL_println(struct sequence_of_longs s)
{
	printf("%d %p\n", s.length, s.items);
//	printf("%d %p %ld\n", s.length, s.items, *s.items);
}

int main(void)
{
//	struct sequence_of_longs sequence;
	struct sequence_of_longs sequence = {};
//	struct sequence_of_longs sequence = {
//		items: NULL,
//		length: 0
//	};

	SEQL_println(sequence);

	return EXIT_SUCCESS;
}
