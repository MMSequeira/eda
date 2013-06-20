
// `array_of_doubles.c` &ndash; Utilitários para _arrays_ de `double`
// ==================================================================
//
// Este é o ficheiro de implementação correspondente ao ficheiro de
// cabeçalho ou de interface [`array_of_double.h`](array_of_doubles.h.html). Ambos
// correspondem ao módulo físico `array_of_double`, cujo objectivo é fornecer um
// conjunto de ferramentas para lidar com _arrays_ de `double`.
//
// Note que optámos por _não_ incluir comentários de documentação
// [Doxygen](http://doxygen.org/) em nenhum dos módulos deste programa.

// Começamos por incluir o próprio ficheiro de interface. Isso ajuda-nos a
// garantir a coerência entre os dois ficheiros, pois desta forma o compilador
// poderá gerar erros quando detectar incoerências.
#include "array_of_doubles.h"

// Inclusões de ficheiros de interface
// -----------------------------------
//
// Começamos por incluir os vários ficheiro de interface necessários:
//
// - `stdlib.h` &ndash; Para podermos usar o valor especial `NULL` dos ponteiros
//   e para podemos usar as rotinas `malloc()` e `realloc()` e o procedimento
//   `qsort()`.
//
// - `stdio.h` &ndash; Para podermos usar as rotinas `fopen()`, `fclose()` e
//   `fscanf()`.
//
// - `math.h` &ndash; Para podermos usar a função `sqrt()` e as macros `NAN` e
//   `INFINITY`.
//
// - `assert.h` &ndash; Para podermos usar a macro `assert()`.
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

// Definições de rotinas
// ---------------------

// ### `new_double_array_of()`
//
// Note como classificamos `length` como `const`. Esta prática ajuda o
// compilador a detectar os nossos próprios erros. Ao afirmarmos explicitamente
// que não tencionamos alterar um parâmetro, permitimos que o compilador detecte
// alterações realizadas por engano. Seguimos esta prática em todo o código
// deste projecto.
double *new_double_array_of(const int length)
{
	assert(length >= 0);

	return malloc(length * sizeof(double));
}

// ### `resize_double_array_to()`
double *resize_double_array_to(double *const items, const int new_length)
{
	assert(new_length >= 0);

	return realloc(items, new_length * sizeof(double));
}

// ### `read_double_array_from()`
double *read_double_array_from(const char *const file_name, int *const length)
{
	assert(file_name != NULL);
	assert(length != NULL);

	// Começamos por abrir um novo canal de leitura para o ficheiro cujo
	// nome recebemos como argumento.
	FILE *file = fopen(file_name, "r");

	// Em C, o código que lida com casos de erro e casos excepcionais
	// emaranha-se com o código «normal». Isso torna todo o código menos
	// legível. Para evitar este problema a melhor solução é mesmo mudar de
	// linguagem. :-)
	if (file == NULL)
		return NULL;

	// O _array_ onde iremos guardando os itens lidos tem de ir crescendo à medida que a leitura prossegue. Em cada instante, o _array_ terá como capacidade o valor guardado nesta variável. 
	int capacity = 32;

	double *items = new_double_array_of(capacity);

	if (items == NULL) {
		fclose(file);
		return NULL;
	}

	int i = 0;
	double item;
	while (fscanf(file, "%lg", &item) == 1) {
		if (i == capacity)
			items = resize_double_array_to(items, capacity *= 2);
		items[i++] = item;
	}

	*length = i;

	if (*length != capacity)
			items = resize_double_array_to(items, *length);

	fclose(file);

	return items;
}

void copy_double_array(const int length,
		double copy[length], const double original[length])
{
	assert(length >= 0);
	assert(length == 0 || copy != NULL);
	assert(length == 0 || original != NULL);

	for (int i = 0; i != length; i++)
		copy[i] = original[i];
}

bool double_arrays_equal(int length,
			const double first[length], const double second[length])
{
	assert(length >= 0);
	assert(length == 0 || first != NULL);
	assert(length == 0 || second != NULL);

	int i = 0;
	while(i != length && first[i] == second[i])
		i++;
	return i == length;
}

static int compare(const void *first_generic, const void *second_generic)
{
	const double *first = first_generic;
	const double *second = second_generic;

	if (first < second)
		return -1;
	else if(first > second)
		return 1;
	else
		return 0;
}

double double_array_average(int length, const double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	double sum = 0.0;

	for (int i = 0; i != length; i++)
		sum += items[i];

	return sum / length;
}

static double square_of(const double value)
{
	return value * value;
}

double double_array_stddev(int length, const double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	const double average = double_array_average(length, items);

	double sum = 0.0;

	for (int i = 0; i != length; i++)
		sum += square_of(items[i] - average);

	return sqrt(sum / length);
}

double double_array_median(int length, const double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	if (length == 0)
		return NAN;

	double work_items[length];
	copy_double_array(length, work_items, items);

	qsort(work_items, length, sizeof(double), compare);

	if (length % 2 == 0)
		return (work_items[length / 2 - 1] + work_items[length / 2]) / 2;
	else
		return work_items[length / 2];
}

double double_array_minimum(int length, const double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	double minimum = INFINITY;

	for (int i = 0; i != length; i++)
		if (items[i] < minimum)
			minimum = items[i];

	return minimum;
}

double double_array_maximum(int length, const double items[length])
{
	assert(length > 0);
	assert(length == 0 || items != NULL);

	double maximum = -INFINITY;

	for (int i = 0; i != length; i++)
		if (items[i] > maximum)
			maximum = items[i];

	return maximum;
}

struct double_statistics double_array_statistics(const int length,
						const double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	struct double_statistics statistics = {
		.average = NAN,
		.stddev = NAN,
		.median = NAN,
		.minimum = INFINITY,
		.maximum = -INFINITY
	};

	if (length == 0)
		return statistics;

	double work_items[length];

	double sum = 0.0;
	double sum_of_squares = 0.0;

	for (int i = 0; i != length; i++) {
		work_items[i] = items[i];
		sum += items[i];
		sum_of_squares += square_of(items[i]);
	}

	statistics.average = sum / length;
	statistics.stddev =
		sqrt(sum_of_squares / length - square_of(statistics.average));

	qsort(work_items, length, sizeof(double), compare);

	statistics.minimum = work_items[0];

	if (length % 2 == 0)
		statistics.median =
			(work_items[length / 2 - 1] + work_items[length / 2]) / 2;
	else
		statistics.median = work_items[length / 2];

	statistics.maximum = work_items[length - 1];

	return statistics;
}
