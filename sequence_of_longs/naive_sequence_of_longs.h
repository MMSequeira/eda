#ifndef ISLA_EDA_NAIVE_SEQUENCE_OF_LONGS_H_INCLUDED
#define ISLA_EDA_NAIVE_SEQUENCE_OF_LONGS_H_INCLUDED

struct naive_sequence_of_longs;

struct naive_sequence_of_longs *NSEQL_new(void);

void NSEQL_print(struct naive_sequence_of_longs *sl);

void NSEQL_println(struct naive_sequence_of_longs *sl);

int NSEQL_length(struct naive_sequence_of_longs *sl);

void NSEQL_add(struct naive_sequence_of_longs *sl, long new_item);

long NSEQL_item(struct naive_sequence_of_longs *sl, int index);

#endif // ISLA_EDA_NAIVE_SEQUENCE_OF_LONGS_H_INCLUDED

