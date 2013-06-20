#ifndef ISLA_EDA_SORTING_ALGORITHMS_H_INCLUDED
#define ISLA_EDA_SORTING_ALGORITHMS_H_INCLUDED

#include <stdbool.h>

struct algorithm_counts {
	int comparisons;
	int swaps;
	int copies;
};

struct sorting_algorithm {
	const char* name;
	bool (*sort)(int, double[]);
	bool (*sort_and_count)(int, double[], struct algorithm_counts*);
};

extern const struct sorting_algorithm sorting_algorithms[];
extern const int number_of_sorting_algorithms;

bool bubble_sort(int length, double items[length]);

bool selection_sort(int length, double items[length]);

bool insertion_sort(int length, double items[length]);

bool shell_sort(int length, double items[length]);

bool quicksort(int length, double items[length]);

bool merge_sort(int length, double items[length]);

bool bubble_sort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

bool selection_sort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

bool insertion_sort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

bool shell_sort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

bool quicksort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

bool merge_sort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

#endif // ISLA_EDA_SORTING_ALGORITHMS_H_INCLUDED
