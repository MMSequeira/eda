#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#include "array_of_doubles.h"
#include "sorting_algorithms.h"

const clock_t clock_precision = 1000000U /* CLOCKS */;

const double threshold_repetition_time = 300.0 /* seconds */;

const double threshold_time_per_sort = 300.0 /* seconds */;

const int maximum_file_size = 1 << 24;
//const int maximum_file_size = 1 << 10;

const int maximum_number_of_repetions = 1001;

const char *file_types[] = {
	"sorted",
	"partially_sorted",
	"shuffled"
};
const int number_of_file_types = sizeof(file_types) / sizeof(file_types[0]);

struct algorithm_statistics {
	struct algorithm_counts counts;
	int accumulated_runs;
	int repetitions;
	struct double_statistics times;
};

const struct algorithm_statistics initial_statistics = {
	.counts = {
		.comparisons = 0,
		.swaps = 0,
		.copies = 0
	},
	.accumulated_runs = 0,
	.repetitions = 0,
	.times = {
		.average = NAN,
		.stddev = NAN,
		.median = NAN,
		.minimum = NAN,
		.maximum = NAN
	}
};

static bool valid_file_type(const char* file_type)
{
	for (int i = 0; i != number_of_file_types; i++)
		if (strcmp(file_type, file_types[i]) == 0)
			return true;

	return false;
}

static double copy_time_estimate(const int length, double work_items[length],
				const double items[length])
{
	printf("\tEstimating copy time...\n");

	int runs = 0;
	clock_t start = clock();
	do {
		copy_double_array(length, work_items, items);
		runs++;
	} while(clock() - start < clock_precision);

	start = clock();
	for (int i = 0; i != runs; i++)
		copy_double_array(length, work_items, items);
	double copy_time = (double) (clock() - start) / CLOCKS_PER_SEC / runs;

	printf("\tCopy time estimated to be %g seconds (based on %d runs).\n",
		copy_time, runs);

	return copy_time;
}

double sort_time_estimate(struct sorting_algorithm algorithm,
			const int length,
			double work_items[length], const double items[length],
			const int runs, const double copy_time)
{
	clock_t start = clock();
	for (int i = 0; i != runs; i++) {
		copy_double_array(length, work_items, items);
		if(!algorithm.sort(length, work_items)) {
			fprintf(stderr, "Error: could not run sorting algorithm "
				"'%s'.\n", algorithm.name);
			return false;
		}
	}

	return (double) (clock() - start) / CLOCKS_PER_SEC / runs - copy_time;
}

int number_of_runs(const struct sorting_algorithm algorithm,
		const int length, const double items[length],
		double work_items[length],
		const double copy_time)
{
	int runs = 0;
	clock_t start = clock();
	do {
		copy_double_array(length, work_items, items);

		if(!algorithm.sort(length, work_items)) {
			fprintf(stderr, "Error: could not run sorting algorithm '%s'.\n",
				algorithm.name);
			return -1;
		}

		runs++;
	} while(clock() - start - runs * copy_time * CLOCKS_PER_SEC <
		clock_precision);

	return runs;
}

static bool run_experiment(const struct sorting_algorithm algorithm,
		const int length,
		const double items[length],
		double work_items[length],
		const double sorted_items[length],
		struct algorithm_statistics *statistics,
		const double copy_time)
{
	*statistics = initial_statistics;

	copy_double_array(length, work_items, items);

	printf("\t\tRunning counting algorithm version.\n");

	if (!algorithm.sort_and_count(length, work_items, &statistics->counts)) {
		fprintf(stderr, "Error: could not run sorting algorithm '%s' "
			"(counting version).\n", algorithm.name);
		return false;
	}

	printf("\t\tChecking correctness of counting algorithm version.\n");

	if (!double_arrays_equal(length, sorted_items, work_items)) {
		fprintf(stderr, "Error: sorting algorithm '%s' (counting "
			"version) did not sort.\n", algorithm.name);
		return false;
	}

	copy_double_array(length, work_items, items);

	printf("\t\tRunning non-counting algorithm version.\n");

	if(!algorithm.sort(length, work_items)) {
		fprintf(stderr, "Error: could not run sorting algorithm '%s'.\n",
			algorithm.name);
		return false;
	}

	printf("\t\tChecking correctness of non-counting algorithm version.\n");

	if (!double_arrays_equal(length, sorted_items, work_items)) {
		fprintf(stderr, "Error: sorting algorithm '%s' did not sort.\n",
			algorithm.name);
		return false;
	}

	printf("\t\tTime measurements:\n");

	int runs =
		number_of_runs(algorithm, length, items, work_items, copy_time);

	if (runs < 0)
		return false;

	printf("\t\t\tEach time will be estimated using %d runs.\n", runs);

	statistics->accumulated_runs = runs;

	double times[maximum_number_of_repetions];

	printf("\t\t\tStarting repeated estimations:\n");

	int repetitions = 0;
	clock_t start = clock();
	double accumulated_time;

	do {
		times[repetitions] =
			sort_time_estimate(algorithm, length, work_items, items,
					runs, copy_time);

		repetitions++;

		accumulated_time = (double)(clock() - start) / CLOCKS_PER_SEC;
	} while(repetitions != maximum_number_of_repetions &&
		accumulated_time < threshold_repetition_time);

	printf("\t\t\t%d repetitions in %g seconds.\n", repetitions,
		accumulated_time);

	statistics->repetitions = repetitions;

	statistics->times = double_array_statistics(repetitions, times);

	return true;
}

static void write_statistics_headers(FILE *const output,
				const char* name)
{
	fprintf(output, ";Comparisons (%s)", name);
	fprintf(output, ";Swaps (%s)", name);
	fprintf(output, ";Copies (%s)", name);
	fprintf(output, ";Accumulated runs (%s)", name);
	fprintf(output, ";Repetitions (%s)", name);
	fprintf(output, ";Time Average [seconds] (%s)", name);
	fprintf(output, ";Time Stddev [seconds] (%s)", name);
	fprintf(output, ";Time Median [seconds] (%s)", name);
	fprintf(output, ";Time Minimum [seconds] (%s)", name);
	fprintf(output, ";Time Maximum [seconds] (%s)", name);
}

static void write_statistics(FILE *const output,
			const struct algorithm_statistics statistics)
{
	fprintf(output, ";%d", statistics.counts.comparisons);
	fprintf(output, ";%d", statistics.counts.swaps);
	fprintf(output, ";%d", statistics.counts.copies);
	fprintf(output, ";%d", statistics.accumulated_runs);
	fprintf(output, ";%d", statistics.repetitions);
	fprintf(output, ";%g", statistics.times.average);
	fprintf(output, ";%g", statistics.times.stddev);
	fprintf(output, ";%g", statistics.times.median);
	fprintf(output, ";%g", statistics.times.minimum);
	fprintf(output, ";%g", statistics.times.maximum);
}

static void run_experiments(const char *const path, const char *const file_type,
		const char *const statistics_file_name)
{
	FILE* output = fopen(statistics_file_name, "w");

	if (output == NULL)  {
		fprintf(stderr, "Error: Could not open '%s' for writing!\n",
			statistics_file_name);
		exit(EXIT_FAILURE);
	}

	fprintf(output, "\"Size\"");
	for (int a = 0; a != number_of_sorting_algorithms; a++)
		write_statistics_headers(output, sorting_algorithms[a].name);

	fputc('\n', output);

	printf("Wrote headers to results.\n");

	bool threshold_time_per_sort_exceeded[number_of_sorting_algorithms];

	for (int a = 0; a != number_of_sorting_algorithms; a++)
		threshold_time_per_sort_exceeded[a] = false;

	for (int s = 2; s != maximum_file_size << 1; s *= 2) {
		char file_name[FILENAME_MAX];
		snprintf(file_name, FILENAME_MAX, "%s%s_%d.txt",
			path, file_type, s);

		printf("Starting experiments for size %d:\n", s);

		char sorted_file_name[FILENAME_MAX];
		snprintf(sorted_file_name, FILENAME_MAX, "%ssorted_%d.txt",
			path, s);

		int length;
		double *const items =
			read_double_array_from(file_name, &length);

		if (items == NULL || length != s) {
			fprintf(stderr, "Error: Reading file '%s'.", file_name);
			fclose(output);
			free(items);
			exit(EXIT_FAILURE);
		}

		double *const sorted_items =
			read_double_array_from(sorted_file_name, &length);

		if (sorted_items == NULL || length != s) {
			fprintf(stderr, "Error: Reading file '%s'.",
				sorted_file_name);
			fclose(output);
			free(items);
			free(sorted_items);
			exit(EXIT_FAILURE);
		}

		double *const work_items = new_double_array_of(length);

		if (sorted_items == NULL) {
			fprintf(stderr, "Error: Reading file '%s'.",
				sorted_file_name);
			fclose(output);
			free(items);
			free(sorted_items);
			exit(EXIT_FAILURE);
		}

		double copy_time = copy_time_estimate(length, work_items, items);

		fprintf(output, "%d", s);
		for (int a = 0; a != number_of_sorting_algorithms; a++) {
			if (threshold_time_per_sort_exceeded[a])
				continue;

			printf("\tStarting experiments for %s:\n",
				sorting_algorithms[a].name);

			struct algorithm_statistics statistics;

			if (!run_experiment(sorting_algorithms[a], length,
						items, work_items, sorted_items,
						&statistics, copy_time)) {
				free(items);
				free(sorted_items);
				free(work_items);
				fclose(output);
				exit(EXIT_FAILURE);
			}

			printf("\t\tWriting results.\n");

			write_statistics(output, statistics);

			printf("\t\tEnding experiments for %s.\n",
				sorting_algorithms[a].name);

			if (statistics.times.median > threshold_time_per_sort)
				threshold_time_per_sort_exceeded[a] = true;
		}

		fputc('\n', output);

		printf("\tEnded experiments for size %d.\n", s);

		free(work_items);
		free(sorted_items);
		free(items);
	}

	fclose(output);
}

int main(int argument_count, char *argument_values[argument_count])
{
	if (argument_count < 4) {
		fprintf(stderr, "Error: Insuficient number of arguments!\n");
		return EXIT_FAILURE;
	}

	const char *const path = argument_values[1];
	const char *const file_type = argument_values[2];
	const char *const statistics_file_name = argument_values[3];

	if (!valid_file_type(file_type)) {
		fprintf(stderr, "Error: Unknown file type '%s'!\n", file_type);
		return EXIT_FAILURE;
	}

	printf("Starting experiments from %s files in %s. Storing results "
		"in %s.\n", file_type, path, statistics_file_name);

	printf("CLOCKS_PER_SEC = %ju\n", (uintmax_t)CLOCKS_PER_SEC);
	printf("double_array_median(0, NULL) = %g\n",
		double_array_median(0, NULL));
	printf("double_array_minimum(0, NULL) = %g\n",
		double_array_minimum(0, NULL));
	printf("double_array_maximum(0, NULL) = %g\n",
		double_array_maximum(0, NULL));

	run_experiments(path, file_type, statistics_file_name);

	return EXIT_SUCCESS;
}
