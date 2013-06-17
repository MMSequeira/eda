#include "sorting_algorithms.h"

#include <stdlib.h>
#include <assert.h>

static void swap(const int length, double items[length],
		const int i, const int j)
{
	assert(0 <= i && i < length);
	assert(0 <= j && j < length);
	assert(items != NULL);

	const double original_item_i = items[i];
	items[i] = items[j];
	items[j] = original_item_i;
}

static void swap_and_count(const int length, double items[length],
			const int i, const int j,
			struct algorithm_counts* counts)
{
	assert(0 <= i && i < length);
	assert(0 <= j && j < length);
	assert(items != NULL);

	const double original_item_i = items[i];
	items[i] = items[j];
	items[j] = original_item_i;

	counts->number_of_swaps++;
	counts->number_of_copies += 3;
}

void bubble_sort(const int length, double items[length])
{
	for (int number_of_unsorted_items = length;
		number_of_unsorted_items != 1;
		number_of_unsorted_items--)
		for (int i = 0; i != number_of_unsorted_items - 1; i++)
			if (items[i] > items[i + 1])
				swap(length, items, i, i + 1);
}

void bubble_sort_and_counts(const int length, double items[length],
			struct algorithm_counts* counts)
{
	for (int number_of_unsorted_items = length;
		number_of_unsorted_items != 1;
		number_of_unsorted_items--)
		for (int i = 0; i != number_of_unsorted_items - 1; i++) {
			counts->number_of_comparisons++;
			if (items[i] > items[i + 1])
				swap_and_count(length, items, i, i + 1, counts);
		}
}

void selection_sort(int length, double items[length]);

void selection_sort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);

void insertion_sort(int length, double items[length]);

void insertion_sort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);

void shell_sort(int length, double items[length]);

void shell_sort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);

void quicksort(int length, double items[length]);

void quicksort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);

void merge_sort(int length, double items[length]);

void merge_sort_and_counts(int length, double items[length],
			struct algorithm_counts* counts);
