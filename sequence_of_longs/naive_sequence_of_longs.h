#ifndef ISLA_EDA_NAIVE_naive_sequence_of_longs_HEADER
#define ISLA_EDA_NAIVE_naive_sequence_of_longs_HEADER

struct naive_sequence_of_longs {
	long *items;
	int length;
};

void NSEQL_print(struct naive_sequence_of_longs *sl);

void NSEQL_println(struct naive_sequence_of_longs *sl);

void NSEQL_initialize(struct naive_sequence_of_longs *sl);

int NSEQL_length(struct naive_sequence_of_longs *sl);

void NSEQL_add(struct naive_sequence_of_longs *sl, long new_item);

long NSEQL_item(struct naive_sequence_of_longs *sl, int index);

#endif // ISLA_EDA_naive_sequence_of_longs_HEADER

