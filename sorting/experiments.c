#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "sorting_algorithms.h"

const int clock_precision = 3;
const double threshold_time_per_sort = 600.0;

const char *file_types[] = {
	"sorted",
	"partially_sorted",
	"shuffled"
};
const int number_of_file_types = sizeof(file_types) / sizeof(file_types[0]);

//const int maximum_file_size = 1 << 24;
const int maximum_file_size = 1 << 7;
const int maximum_number_of_repetions = 100;

static bool valid_file_type(const char* file_type)
{
	for (int i = 0; i != number_of_file_types; i++)
		if (strcmp(file_type, file_types[i]) == 0)
			return true;

	return false;
}

struct algorithm_statistics {
	struct algorithm_counts counts;
	int number_of_clock_accumulated_runs;
	int number_of_repetitions;
	double runtime_average;
	double runtime_stddev;
	double runtime_median;
	double runtime_minimum;
	double runtime_maximum;
};

const struct algorithm_statistics initial_statistics = {
	.counts = {
		.number_of_comparisons = 0,
		.number_of_swaps = 0,
		.number_of_copies = 0},
	.number_of_clock_accumulated_runs = 0,
	.number_of_repetitions = 0,
	.runtime_average = 0.0,
	.runtime_stddev = 0.0,
	.runtime_median = 0.0,
	.runtime_minimum = 0.0,
	.runtime_maximum = 0.0,
};

struct algorithm_statistics run_experiment(const char* file_name) {
	struct algorithm_statistics statistics = initial_statistics;
//	given file
//	given algorithm
//
//	first run count version to get counts
//      then run estimator of clock accumulation runs
//	then run repetitions up to maximum repetitions and time threshold
//	each repetition is call to measure_sort_time, which deals with clock issues
	return statistics;
}

void run_experiments(const char* path, const char* file_type)
{
	for (int size = 2; size != maximum_file_size << 1; size *= 2) {
		char file_name[FILENAME_MAX];
		snprintf(file_name, FILENAME_MAX, "%s%s_%d.txt",
			path, file_type, size);

		printf("The file name is: '%s'\n", file_name);

		// Pass also the procedures to use (counting and non-counting).
		struct algorithm_statistics statistics =
			run_experiment(file_name);
	}
}

int main(int argument_count, char *argument_values[argument_count])
{
	if (argument_count < 3) {
		fprintf(stderr, "Error: Insuficient number of arguments!\n");
		return EXIT_FAILURE;
	}

	if (!valid_file_type(argument_values[2])) {
		fprintf(stderr, "Error! Unknown file type '%s'!\n",
			argument_values[1]);
		return EXIT_FAILURE;
	}

	run_experiments(argument_values[1], argument_values[2]);

	return EXIT_SUCCESS;
}
