#ifndef ISLA_EDA_SEQUENCE_OF_LONGS_HEADER
#define ISLA_EDA_SEQUENCE_OF_LONGS_HEADER

struct sequence_of_longs {
	long *items;
	int length;
	int capacity;
};

void SEQL_print(struct sequence_of_longs *sl);

void SEQL_println(struct sequence_of_longs *sl);

void SEQL_initialize(struct sequence_of_longs *sl);

int SEQL_length(struct sequence_of_longs *sl);

void SEQL_add(struct sequence_of_longs *sl, long new_item);

long SEQL_item(struct sequence_of_longs *sl, int index);

#endif // ISLA_EDA_SEQUENCE_OF_LONGS_HEADER
