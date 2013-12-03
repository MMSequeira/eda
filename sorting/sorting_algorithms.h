// `sorting_algorithms.h` &ndash; Rotinas de ordenação de _arrays_ de `double`
// ===========================================================================
//
// Este é o ficheiro de cabeçalho ou de interface correspondente ao ficheiro de
// implementação [`sorting_algorithms.c`](sorting_algorithms.c.html). Ambos
// correspondem ao módulo físico `sorting_algorithms`, cujo objectivo é fornecer
// um conjunto de ferramentas para lidar com a ordenação de _arrays_ de
// `double`. As rotinas fornecidas implementam alguns dos mais conhecidos
// algoritmos de ordenação:
//
// - Ordenação por bolha ou _bubble sort_.
// - Ordenação por selecção ou _selection sort_.
// - Ordenação por inserção ou _insertion sort_.
// - Ordenação de Shell ou _Shell sort_.
// - Ordenação rápida ou _quicksort_.
// - Ordenação por fusão ou _merge sort_.
//
// Este módulo foi concebido para o estudo da algoritmia. Por isso, para além de
// uma implementação «normal» de cada um dos algoritmos, existe uma outra que é
// em tudo igual mas que regista o número de operações elementares realizadas.
//
// Note que optámos por _não_ incluir comentários de documentação
// [Doxygen](http://doxygen.org/) em nenhum dos módulos deste programa.

// A usual protecção contra os efeitos nefastos da inclusão múltipla.
#ifndef ISLA_EDA_SORTING_ALGORITHMS_H_INCLUDED
#define ISLA_EDA_SORTING_ALGORITHMS_H_INCLUDED

// Incluímos o ficheiro de interface `stdbool.h` para podermos usar o tipo
// `bool` e os seus dois valores `true` e `false`.
#include <stdbool.h>

// Definições de tipos
// ===================

// As rotinas de ordenação que registam o número de operações elementares
// realizadas durante a ordenação de uma _array_ recorrem a esta estrutura para
// guardar as suas contagens.
struct algorithm_counts {
	// Este campo regista o número de comparações envolvendo pelo menos um
	// item do _array_ em ordenação.
	long comparisons;
	// Este campo regista o número de trocas de valores entre pares itens do
	// _array_ em ordenação.
	long swaps;
	// Este campo regista o número de cópias de valores envolvendo pelo
	// menos um item do _array_ em ordenação.
	long copies;
};

// Esta estrutura guarda informação acerca de um algoritmo.
struct sorting_algorithm {
	// Este campo guarda o nome do algoritmo na forma de uma cadeia de
	// caracteres.
	const char* name;
	// Este campo guarda um ponteiro para a rotina que implementa o
	// algoritmo em causa e que _não_ efectua contagem de operações
	// elementares.
	bool (*sort)(int, double[]);
	// Este campo guarda um ponteiro para a rotina que implementa o
	// algoritmo em causa e que efectua contagem de operações elementares.
	bool (*sort_and_count)(int, double[], struct algorithm_counts*);
};

// Declaração de constantes globais
// ================================

// Este _array_ guarda a colecção dos algoritmos considerados, incluindo o seu
// nome e as rotinas que o implementam.
extern const struct sorting_algorithm sorting_algorithms[];

// Esta constante guarda o número de algoritmos considerados.
extern const int number_of_sorting_algorithms;

// Declaração das rotinas de ordenação
// ===================================

// ### Rotinas sem contagem de operações elementares

// Ordenação por bolha ou _bubble sort_.
bool bubble_sort(int length, double items[length]);

// Ordenação por selecção ou _selection sort_.
bool selection_sort(int length, double items[length]);

// Ordenação por inserção ou _insertion sort_.
bool insertion_sort(int length, double items[length]);

// Ordenação de Shell ou _Shell sort_.
bool shell_sort(int length, double items[length]);

// Ordenação rápida ou _quicksort_.
bool quicksort(int length, double items[length]);

// Ordenação por fusão ou _merge sort_.
bool merge_sort(int length, double items[length]);

// ### Rotinas sem contagem de operações elementares

// Ordenação por bolha ou _bubble sort_.
bool bubble_sort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

// Ordenação por selecção ou _selection sort_.
bool selection_sort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

// Ordenação por inserção ou _insertion sort_.
bool insertion_sort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

// Ordenação de Shell ou _Shell sort_.
bool shell_sort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

// Ordenação rápida ou _quicksort_.
bool quicksort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

// Ordenação por fusão ou _merge sort_.
bool merge_sort_and_count(int length, double items[length],
			struct algorithm_counts* counts);

#endif // ISLA_EDA_SORTING_ALGORITHMS_H_INCLUDED
