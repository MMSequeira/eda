// `array_of_doubles.h` &ndash; Utilitários para _arrays_ de `double`
// ==================================================================
//
// Este é o ficheiro de cabeçalho ou de interface correspondente ao ficheiro de
// implementação [`array_of_double.c`](array_of_doubles.c.html). Ambos
// correspondem ao módulo físico `array_of_double`, cujo objectivo é fornecer um
// conjunto de ferramentas para lidar com _arrays_ de `double`.
//
// Note que optámos por _não_ incluir comentários de documentação
// [Doxygen](http://doxygen.org/) em nenhum dos módulos deste programa.

// A usual protecção contra os efeitos nefastos da inclusão múltipla.
#ifndef ISLA_EDA_ARRAY_OF_DOUBLES_HH_INCLUDED
#define ISLA_EDA_ARRAY_OF_DOUBLES_HH_INCLUDED

// Incluímos o ficheiro de interface `stdbool.h` para podermos usar o tipo
// `bool` e os seus dois valores `true` e `false`.
#include <stdbool.h>

// Para podemos calcular a partir de _arrays_ de `double`, de uma só vez, todas
// as estatísticas em que estamos interessados, é conveniente usar uma estrutura
// para as representar.
struct double_statistics {
	// A média e o desvio padrão.
	double average;
	double stddev;
	// A mediana, o valor mínimo e o valor máximo.
	double median;
	double minimum;
	double maximum;
};

// Rotina que cria um novo _array_ com `length` items `double`, todos por
// inicializar. Devolve um ponteiro para o novo _array_. Devolve `NULL` em caso
// de erro.
double *new_double_array_of(long length);

// Rotina que redimensiona um _array_ de `double` `items` recebido como
// argumento de modo a passar a conter `new_length` itens. Devolve um ponteiro
// para o _array_ redimensionado. O ponteiro devolvido pode ser igual ao
// ponteiro recebido como argumento, mas o é necessariamente. Se o _array_
// crescer, os novos itens estarão por inicializar. Devolve `NULL` em caso de
// erro. O valor de `new_length` não pode ser negativo. O valor de `items` pode
// ser `NULL`. Nesse caso admite-se que o _array_ a dimensionar tem zero itens.
double *resize_double_array_to(double *items, long new_length);

// Rotina que lê todos os `double` que conseguir a partir do ficheiro cujo nome
// é passado como argumento e os guarda num _array_. Devolve o _array_ com os
// valores lidos do ficheiro. Devolve `NULL` em caso de erro. Em caso de
// sucesso, altera o inteiro apontado por `length` para o número de `double`
// lidos. Os valores de `file_name` e de `length` não podem ser `NULL`.
double *read_double_array_from(const char *file_name, long *length);

// Procedimento que copia todos os `length` itens do _array_ de `double`
// `original` para o _array_ de `double` `copy`. Ambos os _arrays_ têm de conter
// pelo menos `length` items. O valor de `length` tem de ser não negativo. Os
// valores de `original` e de `copy` podem ser nulos, mas apenas se `length`
// tiver o valor zero.
void copy_double_array(long length, double copy[length],
		const double original[length]);

// Predicado que devolve `true` se os primeiros _length_ itens dos _arrays_ de
// `double` `first` e `second` forem iguais. Devolve `false` no caso contrário.
// O valor de `length` não pode ser negativo. Os valores de `first` e `second`
// podem ser `NULL`, mas apenas se o valor de `length` for zero.
bool double_arrays_equal(long length, const double first[length],
			const double second[length]);

// Função que devolve o valor médio dos primeiros `length` itens do _array_ de
// `double` `items`. O valor de `length` não pode ser negativo. Devolve o valor
// especial NaN se `length` for zero. O valor de `items` pode ser `NULL`, mas
// apenas se `length` for zero.
double double_array_average(long length, const double items[length]);

// Função que devolve o desvio padrão dos primeiros `length` itens do _array_ de
// `double` `items`. O valor de `length` não pode ser negativo. Devolve o valor
// especial NaN se `length` for zero. O valor de `items` pode ser `NULL`, mas
// apenas se `length` for zero.
double double_array_stddev(long length, const double items[length]);

// Função que devolve o valor mediano dos primeiros `length` itens do _array_ de
// `double` `items`. O valor de `length` não pode ser negativo. Devolve o valor
// especial NaN se `length` for zero. O valor de `items` pode ser `NULL`, mas
// apenas se `length` for zero.
double double_array_median(long length, const double items[length]);

// Função que devolve o valor mínimo dos primeiros `length` itens do _array_ de
// `double` `items`. O valor de `length` não pode ser negativo. Devolve o valor
// ∞ se `length` for zero. O valor de `items` pode ser `NULL`, mas
// apenas se `length` for zero.
double double_array_minimum(long length, const double items[length]);

// Função que devolve o valor máximo dos primeiros `length` itens do _array_ de
// `double` `items`. O valor de `length` não pode ser negativo. Devolve o valor
// -∞ se `length` for zero. O valor de `items` pode ser `NULL`, mas
// apenas se `length` for zero.
double double_array_maximum(long length, const double items[length]);

// Função que devolve uma instância da estrutura `struct double_statistics`
// contendo várias estatísticas dos primeiros `length` itens do _array_ de
// `double` `items`. O valor de `length` não pode ser negativo. Se `length` for
// zero, a média, o desvio padrão e a mediana têm o valor especial NaN, o mínimo
// tem o valor ∞ e o máximo tem o valor -∞. O valor de `items` pode ser
// `NULL`, mas apenas se `length` for zero.
struct double_statistics double_array_statistics(long length,
						const double items[length]);

// Fecho da protecção contra os efeitos perversos da inclusão múltipla.
#endif // ISLA_EDA_ARRAY_OF_DOUBLES_HH_INCLUDED
