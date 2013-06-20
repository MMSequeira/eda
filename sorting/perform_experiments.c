// `perform_experiments.c` &ndash; Experiências com algoritmos de ordenação
// ========================================================================
//
// Este é o módulo principal do programa para realização de experiências com
// algoritmos de ordenação. O objectivo é obter dados experimentais sobre o
// número de operações elementares realizadas durante a execução dos algoritmos
// de ordenação, bem como sobre o tempo despendido durante essa execução, sempre
// em situações controladas experimentalmente.
//
// Note que optámos por _não_ incluir comentários de documentação
// [Doxygen](http://doxygen.org/) em nenhum dos módulos deste programa.

// Inclusão de ficheiros de interface
// -----------------------------------
//
// As inclusões dividem-se em dois tipos de ficheiros de interface: os que fazem
// parte da biblioteca padrão e os que fazem parte deste projecto.
  
// ### Inclusão de ficheiros de interface da biblioteca padrão
//
// Começamos por incluir os vários ficheiro de interface da biblioteca padrão
// necessários:
//
// - `stdlib.h` &ndash; Para podermos usar os procedimentos `free()` e `exit()`,
//   o valor especial `NULL` dos ponteiros e as constantes de condição de 
//   terminação do programa `EXIT_SUCCESS` e `EXIT_FAILURE`.
//
// - `stdio.h` &ndash; Para podermos usar as rotinas `printf()`, para escrita
//   formatada ecrã, `snprintf()`, escrita segura em cadeia de caracteres,
//   `fopen()` e `fclose()`, para abertura e encerramento de canais ligados a
//   ficheiros, `fprintf()`, para escrita formatada em ficheiros, e `fputc()`,
//   para escrita de caracteres isolados em ficheiros, bem como o tipo `FILE`,
//   representando um canal estabelecido para um ficheiro, e a macro `stderr`,
//   representando o canal de escrita de mensagens de erros.
//
// - `string.h` &ndash; Para podermos usar a função `strcmp()`.
//
// - `time.h` &ndash; Para podermos usar a função `clock()`, o tipo `clock_t` e
//   a macro `CLOCKS_PER_SEC`.
//
// - `stdbool.h` &ndash; Para podermos usar o tipo booleano ou lógico `bool` e
//   os seus dois valores `false` e `true`.
//
// - `math.h` &ndash; Para podermos usar as macros `NAN` e `INFINITY` (ver
//   [`nans_and_other_oddities.c`](nans_and_other_oddities.c.html)).
//
// - `assert.h` &ndash; Para podermos usar a macro `assert()`.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

// ### Inclusão de ficheiros de interface deste projecto
//
// Em seguida incluímos os ficheiros de interface de módulos físicos desde mesmo
// projecto:
//
// - `array_of_doubles.h` &ndash; Ficheiro de interface do módulo
//   `array_of_doubles`, que fornece ferramentas para lidar com _arrays_ de
//   `double` (ver [`array_of_doubles.h`](array_of_doubles.h.html) e
//   [`array_of_doubles.c`](array_of_doubles.c.html)).
//
// - `sorting_algorithms.h` &ndash; Ficheiro de interface do módulo
//   `sorting_algorithms`, que fornece o conjunto de procedimentos de ordenação
//   alvo a experimentação realizada, bem como algumas ferramentas auxiliares
//   (ver [`sorting_algorithms.h`](sorting_algorithms.h.html) e
//   [`sorting_algorithms.c`](sorting_algorithms.c.html)).
#include "array_of_doubles.h"
#include "sorting_algorithms.h"

// Definição de constantes
// -----------------------
//
// Definimos agora algumas constantes que determinam alguns dos parâmetros
// experimentais.
  
// ### `clock_precision`
//
// Expressa em _clocks_, ou seja, em tiques do relógio. Esta constante indica o
// número mínimo de tiques de relógio a usar nas medições. Na máquina em que
// este programa foi testado, o relógio (tal como medido pela função `clock()`)
// tem um valor de `CLOCKS_PER_SEC` de 1&thinsp;000&thinsp;000. Logo, nenhuma
// medição será feita com intervalos de tempo inferiores a 1 segundo. Em
// ambientes onde o valor de `CLOCKS_PER_SEC` seja inferior, poderá ser
// necessário baixar a precisão, sob pena de as experiências se tornarem
// demasiado demoradas.
//
// Quando o tempo de execução de um algoritmo for inferior à precisão dada por
// esta variável, serão realizadas tantas execuções quantas necessárias para
// exceder este tempo, sendo o tempo de cada uma das execuções estimado através
// do quociente entre o tempo total das execuções sucessivas e o número de
// execuções realizadas (subtraindo-se depois o tempo necessário para, através
// de uma cópia, colocar no seu estado inicial, antes de cada ordenação, o
// _array_ a ordenar). Estas execuções sucessivas destinam-se a lidar com
// questões de resolução do relógio usado. Não as confunda com as repetições
// efectuadas com fins estatísticos, pois estas lidam com as flutuações do tempo
// de execução devido às condições de carga da máquina e outros efeitos com
// origem externa ao programa.
static const clock_t clock_precision = 1000000U; // clocks (tics)

// ### `threshold_repetition_time`
//
// Quando o tempo acumulado das repetições das estimativas do tempo de execução
// da ordenação, repetições essas realizadas para fins estatísticos, exceder
// este limiar, as repetições são interrompidas. Este limiar está expresso em
// segundos e tenta garantir que as experiências não se tornam demasiado
// demoradas. Naturalmente, as estatísticas obtidas serão tão piores quanto
// menor for o número de repetições realizadas. Um valor de 300 limita as
// repetições a cerca de cinco minutos.
static const double threshold_repetition_time = 300.0; // seconds

// ### `maximum_number_of_repetions`
//
// O número de repetições a efectuar para fins estatísticos é também limitado
// pelo valor desta constante.
static const int maximum_number_of_repetions = 1001;

// ### `threshold_time_per_sort`
//
// Se o tempo de execução de um dado algoritmo se tornar superior a este limiar
// para uma dada dimensão do _array_ a ordenar, esse algoritmo será excluído das
// experiências realizadas com _arrays_ de maiores dimensões. Tenta-se assim
// impedir que algoritmos particularmente maus impeçam a realização de
// experiências com algoritmos melhores, que são capazes de lidar em tempo
// «útil» com _arrays_ de maiores dimensões.
static const double threshold_time_per_sort = 300.0; // seconds

// ### `maximum_file_size`
//
// A dimensão máxima dos ficheiros a usar nas experiências. Note que recorremos
// a uma colecção fixa de ficheiros com dimensões que são potências de 2 entre 2
// e 2<sup>24</sup> (16&thinsp;777&thinsp;216) itens.
static const int maximum_file_size = 1 << 24;

// ### `file_types` e `number_of_file_types`
//
// A constante `file_types` é um _array_ com os tipos de ficheiros (na forma de
// cadeias de caracteres) na colecção de ficheiros de valores a ordenar. Os
// nomes dos ficheiros seguem o padrão `_tipo___dimensão_`, em que o tipo pode
// ser uma dos valores deste _array_ e a dimensão é uma potência de 2 entre 2 e
// 2<sup>24</sup> (16&thinsp;777&thinsp;216) itens. O número de itens do _array_
// é dado pela constante `number_of_file_types`.
const char *const file_types[] = {
	"sorted",
	"partially_sorted",
	"shuffled"
};
const int number_of_file_types = sizeof(file_types) / sizeof(file_types[0]);

// Estrutura de estatísticas e seu valor inicial
// ---------------------------------------------
  
// ### Estrutura de estatísticas
//
// Esta estrutura serve para guardar as estatísticas resultantes das
// experiências realizadas com um dado algoritmo ordenando um determinado
// _array_ de dados.
struct algorithm_statistics {
	// Contagem do número de comparações, trocas e cópias realizadas. Estes
	// valores são obtidos por contagem determinísticas, não sendo resultado
	// de qualquer outra operação estatística.
	struct algorithm_counts counts;
	// Número de execuções do algoritmo realizadas para atingir a precisão
	// desejada. Estas execuções sucessivas destinam-se a ultrapassar
	// limitações da resolução do relógio usado.
	int accumulated_runs;
	// Número de repetições realizadas para obter as estatísticas de tempos.
	int repetitions;
	// Estatísticas dos tempos de execução do algoritmo, incluindo a sua
	// média, o seu desvio padrão, a mediana, o tempo mínimo e o tempo
	// máximo.
	struct double_statistics times;
};

// ### Valor inicial das estatísticas
//
// Usado para inicializar as estatísticas.
static const struct algorithm_statistics initial_statistics = {
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
		.minimum = INFINITY,
		.maximum = -INFINITY
	}
};

static bool valid_file_type(const char* file_type)
{
	assert(file_type != NULL);

	for (int i = 0; i != number_of_file_types; i++)
		if (strcmp(file_type, file_types[i]) == 0)
			return true;

	return false;
}

static double copy_time_estimate(const int length, double work_items[length],
				const double items[length])
{
	assert(length > 0);
	assert(work_items != NULL);
	assert(items != NULL);

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

static double sort_time_estimate(struct sorting_algorithm algorithm,
				const int length, double work_items[length], 
				const double items[length], const int runs,
				const double copy_time)
{
	assert(length > 0);
	assert(work_items != NULL);
	assert(items != NULL);
	assert(runs > 0);
	assert(copy_time > 0.0);

	clock_t start = clock();
	for (int i = 0; i != runs; i++) {
		copy_double_array(length, work_items, items);
		if(!algorithm.sort(length, work_items)) {
			fprintf(stderr, "Error: could not run sorting "
				"algorithm '%s'.\n", algorithm.name);
			return false;
		}
	}

	return (double) (clock() - start) / CLOCKS_PER_SEC / runs - copy_time;
}

static int number_of_runs(const struct sorting_algorithm algorithm,
			const int length, double work_items[length],
			const double items[length], const double copy_time)
{
	assert(length > 0);
	assert(work_items != NULL);
	assert(items != NULL);
	assert(copy_time > 0.0);

	int runs = 0;
	clock_t start = clock();
	do {
		copy_double_array(length, work_items, items);

		if(!algorithm.sort(length, work_items)) {
			fprintf(stderr, "Error: could not run sorting "
				"algorithm '%s'.\n", algorithm.name);
			return -1;
		}

		runs++;
	} while(clock() - start - runs * copy_time * CLOCKS_PER_SEC <
		clock_precision);

	return runs;
}

static bool run_experiment(const struct sorting_algorithm algorithm,
		const int length,
		double work_items[length],
		const double items[length],
		const double sorted_items[length],
		const double copy_time,
		struct algorithm_statistics *statistics)
{
	assert(length > 0);
	assert(work_items != NULL);
	assert(items != NULL);
	assert(sorted_items != NULL);
	assert(copy_time > 0.0);
	assert(statistics != NULL);

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
		number_of_runs(algorithm, length, work_items, items, copy_time);

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
				const char *algorithm_name)
{
	assert(output != NULL);
	assert(algorithm_name != NULL);

	fprintf(output, ";Comparisons (%s)", algorithm_name);
	fprintf(output, ";Swaps (%s)", algorithm_name);
	fprintf(output, ";Copies (%s)", algorithm_name);
	fprintf(output, ";Accumulated runs (%s)", algorithm_name);
	fprintf(output, ";Repetitions (%s)", algorithm_name);
	fprintf(output, ";Time Average [seconds] (%s)", algorithm_name);
	fprintf(output, ";Time Stddev [seconds] (%s)", algorithm_name);
	fprintf(output, ";Time Median [seconds] (%s)", algorithm_name);
	fprintf(output, ";Time Minimum [seconds] (%s)", algorithm_name);
	fprintf(output, ";Time Maximum [seconds] (%s)", algorithm_name);
}

static void write_statistics(FILE *const output,
			const struct algorithm_statistics statistics)
{
	assert(output != NULL);

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
	assert(path != NULL);
	assert(file_type != NULL);
	assert(statistics_file_name != NULL);

	FILE * const output = fopen(statistics_file_name, "w");

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
						work_items, items, sorted_items,
						copy_time, &statistics)) {
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

int main(const int argument_count,
	const char *const argument_values[argument_count])
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

	run_experiments(path, file_type, statistics_file_name);

	return EXIT_SUCCESS;
}
