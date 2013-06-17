#ifndef ISLA_EDA_SORTING_ALGORITHMS_H_INCLUDED
#define ISLA_EDA_SORTING_ALGORITHMS_H_INCLUDED

struct algorithm_counts {
	int number_of_comparisons;
	int number_of_swaps;
	int number_of_copies;
};

void bubble_sort(int length, double items[length]);

void selection_sort(int length, double items[length]);

void insertion_sort(int length, double items[length]);

void shell_sort(int length, double items[length]);

void quicksort(int length, double items[length]);

void merge_sort(int length, double items[length]);

void bubble_sort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);

void selection_sort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);

void insertion_sort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);

void shell_sort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);

void quicksort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);

void merge_sort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);

#endif // ISLA_EDA_SORTING_ALGORITHMS_H_INCLUDED
