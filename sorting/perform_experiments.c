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

// Quando o tempo acumulado das repetições das estimativas do tempo de execução
// da ordenação, repetições essas realizadas para fins estatísticos, exceder
// este limiar, as repetições são interrompidas. Este limiar está expresso em
// segundos e tenta garantir que as experiências não se tornam demasiado
// demoradas. Naturalmente, as estatísticas obtidas serão tão piores quanto
// menor for o número de repetições realizadas. Um valor de 300 limita as
// repetições a cerca de cinco minutos.
static const double threshold_repetition_time = 300.0; // seconds

// O número de repetições a efectuar para fins estatísticos é também limitado
// pelo valor desta constante.
static const long maximum_number_of_repetions = 1001L;

// Se o tempo de execução de um dado algoritmo se tornar superior a este limiar
// para uma dada dimensão do _array_ a ordenar, esse algoritmo será excluído das
// experiências realizadas com _arrays_ de maiores dimensões. Tenta-se assim
// impedir que algoritmos particularmente maus impeçam a realização de
// experiências com algoritmos melhores, que são capazes de lidar em tempo
// «útil» com _arrays_ de maiores dimensões.
static const double threshold_time_per_sort = 300.0; // seconds

// A dimensão máxima dos ficheiros a usar nas experiências. Note que recorremos
// a uma colecção fixa de ficheiros com dimensões que são potências de 2 entre 2
// e 2<sup>24</sup> (16&thinsp;777&thinsp;216) itens.
static const long maximum_file_size = 1L << 24;

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
	long accumulated_runs;
	// Número de repetições realizadas para obter as estatísticas de tempos.
	long repetitions;
	// Estatísticas dos tempos de execução do algoritmo, incluindo a sua
	// média, o seu desvio padrão, a mediana, o tempo mínimo e o tempo
	// máximo.
	struct double_statistics times;
};

// Constante usada para inicializar as variáveis de estatísticas.
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

// Definição de rotinas
// --------------------

// Predicado que devolve `true` se `file_type` é um dos tipos de ficheiro de
// dados a ordenar suportados pelo programa, i.e., incluídos no _array_
// constante `file_types`.
static bool valid_file_type(const char* file_type)
{
	assert(file_type != NULL);

	int i = 0;
	while (i != number_of_file_types &&
	       strcmp(file_type, file_types[i]) != 0)
		i++;

	return i != number_of_file_types;
}

// Função que devolve uma estimativa do tempo necessário para copiar o conteúdo
// do _array_ `items` para o _array_ `work_items`. Ambos os _arrays_ têm de ter
// pelo menos `length` itens. O tempo é devolvido em segundos. A estimativa é
// realizada com uma precisão dada pela constante `clock_precision`.
static double copy_time_estimate(const long length, double work_items[length],
				 const double items[length])
{
	assert(length > 0L);
	assert(work_items != NULL);
	assert(items != NULL);

	printf("\tEstimating copy time...\n");

	// Um primeiro ciclo estima o número de execuções da cópia necessárias
	// para atingir a precisão pretendida.
	long runs = 0L;
	clock_t start = clock();

	do {
		copy_double_array(length, work_items, items);
		runs++;
	} while(clock() - start < clock_precision);

	// Uma vez que a obtenção da estimativa do número de execuções teve de
	// recorrer a invocações repetidas da função `clock()`, o que poderia
	// viciar uma estimativa do tempo de cópia que se baseasse no tempo de
	// acumulado da execução do ciclo, repetimos o mesmo número de
	// execuções, desta vez sem invocações intermédias à função `clock()`.
	start = clock();

	for (long i = 0L; i != runs; i++)
		copy_double_array(length, work_items, items);

	double copy_time = (double) (clock() - start) / CLOCKS_PER_SEC / runs;

	printf("\tCopy time estimated to be %g seconds (based on %ld runs).\n",
	       copy_time, runs);

	return copy_time;
}

// Função que devolve uma estimativa do tempo de execução do algoritmo de
// ordenação dado por `algorithm`, quando aplicado à ordenação do _array_
// `work_itens` com `length` itens, obtido por cópia do _array_ `items` com o
// mesmo número de itens. A estimativa é realizada recorrendo à acumulação do
// tempo de `runs` execuções sucessivas. Uma vez que cada execução do algoritmo
// tem de ser precedida da cópia dos itens do _array_ `items` para o _array_
// `work_items`, o tempo estimado para essa cópia, `copy_time`, é subtraído ao
// quociente entre o tempo total acumulado e o número de execuções `runs`. Em
// caso de erro, devolve um valor negativo.
static double sort_time_estimate(struct sorting_algorithm algorithm,
				 const long length, double work_items[length],
				 const double items[length], const long runs,
				 const double copy_time)
{
	assert(length > 0L);
	assert(work_items != NULL);
	assert(items != NULL);
	assert(runs > 0L);
	assert(copy_time > 0.0);

	clock_t start = clock();

	for (long i = 0; i != runs; i++) {
		copy_double_array(length, work_items, items);

		if(algorithm.sort(length, work_items)) {
			fprintf(stderr, "Error: could not run sorting "
				"algorithm '%s'.\n", algorithm.name);
			return -1.0;
		}
	}

	return (double) (clock() - start) / CLOCKS_PER_SEC / runs - copy_time;
}

// Devolve uma estimativa do número de execuções do algoritmo de ordenação
// `algorithm`, quando aplicado à ordenação do _array_ `work_itens` com `length`
// itens, obtido por cópia do _array_ `items` com o mesmo número de itens,
// necessárias para atingir a precisão pretendida. O efeito do tempo de cópia
// entre os _arrays_ `copy_time` é cancelado na estimativa efectuadas. Em caso
// de erro devolve um valor negativo.
static long number_of_runs(const struct sorting_algorithm algorithm,
			  const long length, double work_items[length],
			  const double items[length], const double copy_time)
{
	assert(length > 0L);
	assert(work_items != NULL);
	assert(items != NULL);
	assert(copy_time > 0.0);

	long runs = 0L;
	clock_t start = clock();

	do {
		copy_double_array(length, work_items, items);

		if(algorithm.sort(length, work_items)) {
			fprintf(stderr, "Error: could not run sorting "
				"algorithm '%s'.\n", algorithm.name);
			return -1;
		}

		runs++;
	} while(clock() - start - runs * copy_time * CLOCKS_PER_SEC <
		clock_precision);

	return runs;
}

// Esta rotina escuta uma experiência com o algoritmo de ordenação `algorithm`,
// obtendo contagens de operações e estatísticas do tempo de execução
// resultantes da sua aplicação ao _array_ `items`, com comprimento `length`. As
// estatísticas são optidas por aplicação repetida da função
// `sort_time_estimate()`. O _array_ ordenado é sempre `work_itens`, para onde
// os itens originais, contidos em `items`, são copiados antes de cada
// ordenação. Para além da obtenção de contagens e estatísticas, a correcção da
// ordenação obtida é verificada por comparação com o _array_ `sorted_items`,
// que contém os mesmos itens de `items`, mas já ordenados por ordem crescente.
// As estimativa dos tempo de execução são realizadas levando em conta o tempo
// estimado `copy_time` necessário para preparar o _array_ `sorted_items` para
// cada ordenação, copiando os seus itens a partir de `items`. As contagens e
// estatísticas são guardadas na instância de `struct algorithm_statistics`
// apontada pelo ponteiro `statistics`. Em caso de erro devolve o valor `true`.
static bool experiment_algorithm(const struct sorting_algorithm algorithm,
				const long length, double work_items[length],
				const double items[length],
				const double sorted_items[length],
				const double copy_time,
				struct algorithm_statistics *statistics)
{
	assert(length > 0L);
	assert(work_items != NULL);
	assert(items != NULL);
	assert(sorted_items != NULL);
	assert(copy_time > 0.0);
	assert(statistics != NULL);

	// Preparamos o _array_ `work_items` e realizamos uma primeira ordenação
	// invocando o procedimento de ordenação que implementa o algoritmo em
	// causa e que efectua contagem das operações elementares. Dessa forma,
	// não só obtemos as contagens necessárias, como podemos verificar a
	// correcção do resultado da ordenação com essa função, comparando-o com
	// o _array_ `sorted_items`. Em caso de erro, retornamos devolvendo o
	// valor `true`.
	copy_double_array(length, work_items, items);

	printf("\t\tRunning counting algorithm version.\n");

	if (algorithm.sort_and_count(length, work_items, &statistics->counts)) {
		fprintf(stderr, "Error: could not run sorting algorithm '%s' "
			"(counting version).\n", algorithm.name);
		return true;
	}

	printf("\t\tChecking correctness of counting algorithm version.\n");

	if (!double_arrays_equal(length, sorted_items, work_items)) {
		fprintf(stderr, "Error: sorting algorithm '%s' (counting "
			"version) did not sort.\n", algorithm.name);
		return true;
	}

	// Antes de proceder às estimativas dos tempos de execução e ao cálculo
	// das respectivas estatísticas, voltamos a preparar o _array_
	// `work_items` e aplicamos-lhe a versão do procedimento de ordenação
	// que implementa o algoritmo de ordenação em causa _sem efectuar
	// contagens_. Fazemo-lo para podermos verificar a correcção do
	// resultado obtido, da mesma forma que anteriormente. Em caso de erro,
	// retornamos devolvendo o valor `true`.
	copy_double_array(length, work_items, items);

	printf("\t\tRunning non-counting algorithm version.\n");

	if(algorithm.sort(length, work_items)) {
		fprintf(stderr, "Error: could not run sorting algorithm '%s'.\n",
			algorithm.name);
		return true;
	}

	printf("\t\tChecking correctness of non-counting algorithm version.\n");

	if (!double_arrays_equal(length, sorted_items, work_items)) {
		fprintf(stderr, "Error: sorting algorithm '%s' did not sort.\n",
			algorithm.name);
		return true;
	}

	// Feitas as contagens e verificada a correcção das ordenações obtidas
	// por aplicação dos dois procedimentos implementando o algoritmo,
	// podemos começar a estimar os tempos de execução. Estes tempos são
	// estimados usando a versão _sem contagem_ dos procedimentos.
	printf("\t\tTime measurements:\n");

	// Estimamos o número de execuções da ordenação a realizar para obter
	// resultados com a precisão escolhida.  Em caso de erro, retornamos
	// devolvendo o valor `true`.
	long runs =
		number_of_runs(algorithm, length, work_items, items, copy_time);

	if (runs < 0L)
		return true;

	printf("\t\t\tEach time will be estimated using %ld runs.\n", runs);

	// Guardamos o valor obtido na estrutura de estatísticas.
	statistics->accumulated_runs = runs;

	// Os tempos obtidos em cada uma das repetições das estimativas a
	// realizar serão guardados neste _array_.
	double times[maximum_number_of_repetions];

	printf("\t\t\tStarting repeated estimations:\n");

	// Este ciclo repete a obtenção de estimativas do tempo de execução até
	// se atingir o limite máximo de iterações ou até se ultrapassar o
	// limiar do tempo acumulado de execução do ciclo.
	long repetitions = 0L;
	clock_t start = clock();
	double accumulated_time;

	do {
		// Obtemos uma estimativa do tempo de execução do algoritmo. Em
		// caso de erro, retornamos devolvendo o valor `true`.
		times[repetitions] =
			    sort_time_estimate(algorithm, length, work_items,
						items, runs, copy_time);

		if(times[repetitions] < 0.0)
			return true;

		repetitions++;

		accumulated_time = (double)(clock() - start) / CLOCKS_PER_SEC;
	} while(repetitions != maximum_number_of_repetions &&
		accumulated_time < threshold_repetition_time);

	printf("\t\t\t%ld repetitions in %g seconds.\n", repetitions,
	       accumulated_time);

	// Guardamos o valor obtido para as repetições na estrutura de
	// estatísticas.
	statistics->repetitions = repetitions;

	// Calculamos as estatísticas dos tempos de execução obtidos e guardamo-
	// las na estrutura de estatísticas.
	statistics->times = double_array_statistics(repetitions, times);

	// Retornamos devolvendo o valor `false`, indicando que não ocorreram
	// quaisquer erros.
	return false;
}

// Escreve no canal de saída `output` os cabeçalhos das colunas de estatísticas
// para o algoritmo com o nome dado por `lagorithm_name`.
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

// Escreve no canal de saída `output` as estatísticas contidas em `statistics`
// (que dizem respeito a um dado algoritmo).
static void write_statistics(FILE *const output,
			     const struct algorithm_statistics statistics)
{
	assert(output != NULL);

	fprintf(output, ";%ld", statistics.counts.comparisons);
	fprintf(output, ";%ld", statistics.counts.swaps);
	fprintf(output, ";%ld", statistics.counts.copies);
	fprintf(output, ";%ld", statistics.accumulated_runs);
	fprintf(output, ";%ld", statistics.repetitions);
	fprintf(output, ";%g", statistics.times.average);
	fprintf(output, ";%g", statistics.times.stddev);
	fprintf(output, ";%g", statistics.times.median);
	fprintf(output, ";%g", statistics.times.minimum);
	fprintf(output, ";%g", statistics.times.maximum);
}

// Esta rotina executa as experiências para os ficheiros com `size` valores a
// ordenar e para cada algoritmo. Efectuamos as experiências apenas para os
// ficheiros do tipo dado por `file_type` (que pode tomar os valores `sorted`,
// `partially_sorted` e `shuffled`). Lemos os ficheiros a partir da pasta dada
// por `path` (que tem de terminar no caractere separador de pastas
// correspondente ao sistema operativo em que o programa é executado).
// Escrevemos os resultados no canal de saída `output`. Se algum dos algoritmos
// tiver um tempo de execução superior ao limiar definido, actualizamos o
// _array_ `excessive_time_per_sort` de modo a conter o valor `true` na posição
// correspondente a esse algoritmo. Se alguma posição desse _array_ já tiver o
// valor `true`, o algoritmo correspondente não chega a ser experimentado.
// Devolvemos `true` em caso de erro.
bool experiment_size(FILE *const output, const char *const path,
		     const char *const file_type, const long size,
		     bool excessive_time_per_sort[number_of_sorting_algorithms])
{
	// Construímos o nome do ficheiro com o tipo dado por `file_type`, com a
	// dimensão dada por `s` e na pasta dada por `path`. Este ficheiro
	// contém os itens a ordenar.
	char file_name[FILENAME_MAX];
	snprintf(file_name, FILENAME_MAX, "%s%s_%ld.txt", path, file_type, size);

	// Construímos o nome do ficheiro com o tipo `sorted`, com a dimensão
	// `s` e na pasta dada por `path`. Este ficheiro contém os itens já
	// ordenados. O seu conteúdo será usado para verificar a correcção dos
	// algoritmos.
	char sorted_file_name[FILENAME_MAX];
	snprintf(sorted_file_name, FILENAME_MAX, "%ssorted_%ld.txt", path, size);

	// Definimos os ponteiros que apontarão para os _arrays_ dinâmicos
	// necessários para a experiência. Violamos aqui explicitamente a regra
	// de definir as variáveis tão próximo quanto possível do primeiro local
	// em que podem ser inicializadas com um valor relevante. Essa violação
	// decorre do estilo de tratamento de erros usado, que recorre à
	// geralmente pouco recomendável instrução `goto` para se poder «arrumar
	// a casa», em caso de erro, de forma pouco intrusiva no restante
	// código.
	double *items = NULL;
	double *sorted_items = NULL;
	double *work_items = NULL;

	// Lemos o conteúdo do ficheiro com os itens a ordenar para o _array_
	// dinâmico `items` (na realidade um ponteiro para o seu primeiro item).
	// O número de itens lidos fica guardado em `length`. A leitura e
	// criação do _array_ dinâmico podem falhar por falta de memória ou por
	// o ficheiro não conter o número de itens esperado.
	long length;
	items = read_double_array_from(file_name, &length);

	// Definimos a variável `error`, cujo valor indica, em cada momento, se
	// ocorreu algum erro. O estilo de tratamento de erros que adoptámos
	// inspira-se no utilizado no _kernel_ do Linux. Ou seja, os erros são
	// detectados logo que possível e levam a um salto, usando a instrução
	// `goto`, para a secção final e de «arrumação da casa» da rotina em que
	// nos encontramos. Dessa forma o código fica mais simples e
	// compreensível. Em linguagens de mais alto nível que o C há melhores
	// mecanismos para resolver este problema de lidar com os erros de forma
	// elegante.
	//
	// Inicializamos a variável `error` com o valor apropriado, dado o
	// resultado da tentativa de leitura do ficheiro efectuada na instrução
	// anterior.
	bool error = items == NULL || length != size;

	// Em caso de erro escrevemos em `stderr` uma mensagem apropriada e
	// saltamos para a secção de tratamento de erros, a que daremos o nome
	// `terminate`.
	if (error) {
		fprintf(stderr, "Error: Reading file '%s'.\n", file_name);
		goto terminate;
	}

	// Lemos o conteúdo do ficheiro com os itens já ordenados para o _array_
	// dinâmico `sorted_items` (na realidade um ponteiro para o seu primeiro
	// item). O número de itens lidos fica guardado em `length`. A leitura e
	// criação do _array_ dinâmico podem falhar por falta de memória ou por
	// o ficheiro não conter o número de itens esperado. Em caso de falha, o
	// erro é tratado como anteriormente.
	sorted_items = read_double_array_from(sorted_file_name, &length);

	error = sorted_items == NULL || length != size;

	if (error) {
		fprintf(stderr, "Error: Reading file '%s'.\n", sorted_file_name);
		goto terminate;
	}

	// Construímos o _array_ de trabalho, ou seja, o _array_ dinâmico para
	// onde serão copiados os itens a ordenar sempre que necessário e que
	// será ordenado durante as experiências a realizar. O _array_ `items`
	// não será alterado. A criação deste _array_ pode falhar por falta de
	// memória. Criar este _array_ neste local evita a necessidade de o
	// recriar várias vezes durante as experiências. A criação do _array_
	// pode falhar por falta de memória.
	work_items = new_double_array_of(size);

	error = work_items == NULL;

	if (error) {
		fprintf(stderr, "Error: Allocating work array.\n");
		goto terminate;
	}

	// Estimamos o tempo de execução da cópia dos itens do _array_ `items`
	// para o _array_ `work_items`. Este tempo será descontado das
	// estimativas do tempo de execução dos algoritmos, que sem este
	// desconto incluiriam o tempo demorado a copiar os itens para o _array_
	// de trabalho antes de proceder à sua ordenação.
	double copy_time = copy_time_estimate(length, work_items, items);

	// Escrevemos no ficheiro CSV de resultado o valor da primeira coluna,
	// ou seja, a dimensão do ficheiro em ordenação. Ou, o que é o mesmo, o
	// número de itens no _array_ a ordenar.
	fprintf(output, "%ld", size);

	// Percorremos cada um dos algoritmos a experimentar.
	for (int a = 0; a != number_of_sorting_algorithms; a++) {
		// Inicializamos as estatísticas com os valores iniciais.
		struct algorithm_statistics statistics = initial_statistics;

		printf("\tStarting experiments for %s:\n",
		       sorting_algorithms[a].name);

		// Se o tempo de execução do algoritmo corrente não tiver
		// excedido anteriormente (i.e., para uma dimensão inferior do
		// ficheiro a ordenar) o limiar estabelecido, então a
		// experiência será realizada. Caso contrário, os dados
		// guardados no ficheiro de resultado serão os valores guardados
		// na constante `initial_statistics`.
		if (!excessive_time_per_sort[a]) {
			printf("\t\tPerforming experiments.\n");
			// Realizamos a experiência invocando a rotina de
			// experimentação e verificando se ocorreu algum erro
			// durante o processo. A experiência é realizada com o
			// algoritmo `sorting_algorithm[a]`, usando os _arrays_
			// `work_items`, `items` e `sorted_items`, todos com
			// `length` itens. O tempo de cópia `copy_time` é usado
			// para efectuar descontos nos tempos estimados sempre
			// que necessário. Os resultados são guardados na
			// variável `statistics`, cujo endereço é passado à
			// rotina de experimentação. A rotina de experimentação
			// devolve um valor booleano que indica se ocorreu ou
			// não algum erro.
			error = experiment_algorithm(sorting_algorithms[a],
							size, work_items, items,
							sorted_items, copy_time,
							&statistics);
			if (error)
				goto terminate;
		} else
			printf("\t\tSkipping experiments.\n");

		printf("\t\tWriting results, if any.\n");

		// Escrevemos os resultados da experiência, caso esta se tenha
		// realizado. Caso contrário, escreve-se o valor inicial das
		// estatísticas, que assinalarão a experiência como não
		// realizada.
		write_statistics(output, statistics);

		printf("\t\tEnding experiments for %s (median time = %g s).\n",
		       sorting_algorithms[a].name, statistics.times.median);

		// Actualizamos o _array_ que indica se o tempo de ordenação
		// excedeu em algum momento, para o algoritmo corrente, o limiar
		// estabelecido.
		if (statistics.times.median > threshold_time_per_sort)
			excessive_time_per_sort[a] = true;
	}

	// Terminamos a linha de estatísticas escrita no ficheiro CSV de
	// resultado.
	fputc('\n', output);

	// A secção final é dedicada a «arrumar a casa», libertando a memória
	// reservada. Esta secção pode ser executada tanto no caso de não terem
	// ocorrido erros, como no caso de terem ocorrido erros. Neste último
	// caso, pode acontecer que o erro tenha ocorrido antes da criação dos
	// _arrays_ dinâmicos. O código está construído de tal forma que, se
	// isso acontecer, o correspondente ponteiro terá o valor `NULL`, que
	// pode ser passado sem inconveniente à rotina `free()`.
terminate:
	// Libertamos a memória reservada para cada um dos _arrays_
	// dinâmicos.
	free(work_items);
	free(sorted_items);
	free(items);

	// Retornamos devolvendo o valor na variável `error`, ou seja, indicando
	// se ocorreram ou não erros.
	return error;
}

// A rotina principal do programa, que executa as experiências para cada
// dimensão dos ficheiros com valores a ordenar e para cada algoritmo.
// Efectuamos as experiências apenas para os ficheiros do tipo dado por
// `file_type` (que pode tomar os valores `sorted`, `partially_sorted` e
// `shuffled`). Lemos os ficheiros a partir da pasta dada por `path` (que tem de
// terminar no caractere separador de pastas correspondente ao sistema operativo
// em que o programa é executado). Escrevemos os resultados no ficheiro com nome
// dado por `statistics_file_name`. Em caso de erro devolvemos o valor `true`.
static bool experiment_all(const char *const path,
			   const char *const file_type,
			   const char *const statistics_file_name)
{
	assert(path != NULL);
	assert(file_type != NULL);
	assert(statistics_file_name != NULL);

	// Definimos um _array_ de valores booleanos que indicam se, em alguma
	// das experiências já realizada com o correspondente algoritmo se
	// excedeu o limiar do tempo de ordenação. Os algoritmos para os quais
	// isso aconteça deixam de ser usados com ficheiros de maiores
	// dimensões, para evitar que o tempo de execução do programa se torne
	// demasiado grande.
	bool excessive_time_per_sort[number_of_sorting_algorithms];
	for (int a = 0; a != number_of_sorting_algorithms; a++)
		excessive_time_per_sort[a] = false;

	// Abrimos o canal para o ficheiro de resultados. O ficheiro de
	// resultados tem o formato CSV (comma separated values) e usa o
	// caractere «;» como separador. A sua primeira linha contém a
	// identificação dos valores em cada coluna, ou seja, os cabeçalhos
	// correspondentes a cada uma das colunas. As linhas subsequentes têm os
	// valores obtidos experimentalmente, correspondendo cada linha a uma
	// dada dimensão dos ficheiros de entrada. A primeira coluna contém essa
	// dimensão. As colunas subsequentes contém as estatísticas obtidas para
	// cada um dos algoritmos experimentados.
	FILE *const output = fopen(statistics_file_name, "w");

	// Definimos a variável `error`, que indicará em cada instante se até
	// então ocorreu algum erro, e inicializamo-la verificando se a abertura
	// do canal de escrita teve resultado.
	bool error = output == NULL;

	if (error) {
		fprintf(stderr, "Error: Could not open '%s' for writing!\n",
			statistics_file_name);
		goto terminate;
	}

	// Escrevemos o cabeçalho da primeira coluna, que contém a dimensão dos
	// ficheiros usados para obter as estatísticas de cada linha.
	fprintf(output, "Size");

	// Escrevemos os cabeçalhos correspondentes a cada um dos algoritmos.
	for (int a = 0; a != number_of_sorting_algorithms; a++)
		write_statistics_headers(output, sorting_algorithms[a].name);

	// Terminamos a linha de cabeçalho.
	fputc('\n', output);

	printf("Wrote headers to results.\n");

	// Percorremos todas as dimensões de ficheiros, que são potências de 2
	// entre 2 e 2<sup>24</sup>. Este último valor é dado pela constante
	// `maximum_file_size`. A operação realizada na guarda serve para obter
	// o valor 2<sup>25</sup>, valor para o qual a se tornará falsa. O
	// operador `<<` desloca o padrão de _bits_ guardado numa variável
	// inteira de um _bit_ para esquerda, o que corresponde a uma
	// multiplicação por 2.
	for (long size = 1L << 1; size != maximum_file_size << 1; size <<= 1) {
		printf("Starting experiments for size %ld:\n", size);

		// Invocamos a rotina que executa as experiências para a
		// dimensão `size` dos ficheiros e para todos os algoritmos.
		error = experiment_size(output, path, file_type, size,
					excessive_time_per_sort);
		if (error)
			goto terminate;

		fflush(output);

		printf("\tEnded experiments for size %ld.\n", size);
	}

	// Secção de «arrumação da casa».
terminate:
	// Fechamos o canal para o ficheiro CSV de resultado.
	if (output != NULL)
		fclose(output);

	// Retornamos devolvendo o valor na variável `error`, ou seja, indicando
	// se ocorreram ou não erros.
	return error;
}

// Rotina inicial do programa.
int main(const int argument_count,
	 const char *const argument_values[argument_count])
{
	// Os argumentos recebidos através da linha de comandos, incluindo o
	// próprio nome do programa executável, são quatro: esse nome, a pasta
	// onde os ficheiros a ordenar se encontram, o tipo de ficheiros a
	// ordenar e o nome do ficheiro onde os resultados serão escritos no
	// formato CSV, por esta ordem.
	if (argument_count < 4) {
		fprintf(stderr, "Error: Insuficient number of arguments!\n");
		return EXIT_FAILURE;
	}

	const char *const path = argument_values[1];
	const char *const file_type = argument_values[2];
	const char *const statistics_file_name = argument_values[3];

	// Verificamos a correcção do tipo de ficheiro passado na linha de
	// comandos.
	if (!valid_file_type(file_type)) {
		fprintf(stderr, "Error: Unknown file type '%s'!\n", file_type);
		return EXIT_FAILURE;
	}

	printf("Starting experiments from %s files in %s. Storing results "
	       "in %s.\n", file_type, path, statistics_file_name);

	// Executamos o procedimento principal do programa, verificando se essa
	// execução teve sucesso.
	if (experiment_all(path, file_type, statistics_file_name))
		return EXIT_FAILURE;

	// Terminamos assinalando sucesso.
	return EXIT_SUCCESS;
}
