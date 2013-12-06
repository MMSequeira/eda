// `sorting_algorithms.c` &ndash; Rotinas de ordenação de _arrays_ de `double`
// ==================================================================
//
// Este é o ficheiro de implementação correspondente ao ficheiro de
// cabeçalho ou interface [`sorting_algorithms.h`](sorting_algorithms.h.html). Ambos
// correspondem ao módulo físico `sorting_algorithms`, cujo objectivo é fornecer
// um conjunto de ferramentas para lidar com a ordenação de _arrays_ de
// `double`.
//
// Note que optámos por _não_ incluir comentários de documentação
// [Doxygen](http://doxygen.org/) em nenhum dos módulos deste programa.
  
// Inclusões
// ---------
  
// ### Inclusão do próprio ficheiro de interface
//
// Começamos por incluir o próprio ficheiro de interface. Isso ajuda-nos a
// garantir a coerência entre os dois ficheiros, pois desta forma o compilador
// poderá gerar erros quando detectar incoerências.
#include "sorting_algorithms.h"

// ### Inclusão de outros ficheiros de interface
//
// Incluímos os vários ficheiro de interface necessários:
//
// - `stdlib.h` &ndash; Para podermos usar o valor especial `NULL` dos ponteiros
//   e para podemos usar as rotinas `malloc()` e `free()`.
//
// - `assert.h` &ndash; Para podermos usar a macro `assert()`.
//
// - `array_of_doubles.h` &ndash; Para podermos usar as rotinas que
//   desenvolvemos para lidar com _arrays_ de `double`.
#include <stdlib.h>
#include <assert.h>

#include "array_of_doubles.h"

// Definição de constantes globais
// -------------------------------
  
// Definimos a constante global que contém a informação acerca de cada
// algoritmo, incluindo o respectivo nome e os ponteiros para as rotinas que o
// implementam, quer sem, quer com contagem de operações elementares.
const struct sorting_algorithm sorting_algorithms[] = {
	{
		.name = "bubble sort",
		.sort = bubble_sort,
		.sort_and_count = bubble_sort_and_count
	},
	{
		.name = "selection sort",
		.sort = selection_sort,
		.sort_and_count = selection_sort_and_count
	},
	{
		.name = "insertion sort",
		.sort = insertion_sort,
		.sort_and_count = insertion_sort_and_count
	},
	{
		.name = "Shell sort",
		.sort = shell_sort,
		.sort_and_count = shell_sort_and_count
	},
	{
		.name = "quicksort",
		.sort = quicksort,
		.sort_and_count = quicksort_and_count
	},
	{
		.name = "merge sort",
		.sort = merge_sort,
		.sort_and_count = merge_sort_and_count
	},
};

// Definimos a constante contendo o número de algoritmos considerado, i.e.,
// contidos no _array_ anterior.
const int number_of_sorting_algorithms =
	sizeof(sorting_algorithms) / sizeof(sorting_algorithms[0]);

// Definição de rotinas auxiliares genéricas
// -----------------------------------------
//
// Começamos por definir rotinas que, sendo auxiliares, não têm ligação externa,
// ou seja, são definidas usando o qualificador `static`. Mais abaixo definimos
// outras rotinas auxiliares específicas de determinadas implementações de
// rotinas de ordenação.
  
// Troca os valores dos itens com índices `i` e `j` do _array_ `items` com
// comprimento `length`.
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

// Troca os valores dos itens com índices `i` e `j` do _array_ `items` com
// comprimento `length` registando o número de operações elementares realizadas.
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

	counts->swaps++;
	counts->copies += 3;
}

// Definição das rotinas de ordenação
// ----------------------------------
  
// ### Ordenação por bolha ou _bubble sort_
bool bubble_sort(const int length, double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	// _Arrays_ vazios ou com apenas um item estão sempre ordenados, pelo
	// que podemos terminar a execução da rotina.
	if (length <= 1)
		return false;

	// A variável `unsorted` guarda o número de itens que ainda não se sabe
	// se estão ordenados e na sua posição definitiva. Inicialmente tem como
	// valor o comprimento do _array_, pois ainda não se procedeu a qualquer
	// troca. Após cada iteração do ciclo interior, o maior dos itens que
	// ainda não se sabe se estão ordenados «flutua» até à sua posição
	// definitiva, pelo que o valor da variável `unsorted` é decrementado.
	// Conceptualmente, o _array_ está dividido em dois segmentos. Os itens
	// que ainda não se sabe se estão ordenados concentram-se num segmento
	// com `unsorted` itens que se encontra no início do _array_. Os itens
	// que se sabe estarem ordenados concentram-se num segmento com `length`
	// - `unsorted` itens que se encontra no final do _array_. O ciclo
	// principal pára quando só sobra um item que ainda não se sabe se está
	// ordenado e na posição definitiva, justamente porque, sendo o único
	// nessas circunstâncias, terá de estar já na sua posição definitiva!
	for (int unsorted = length; unsorted != 1; unsorted--)
		// O ciclo interior não precisa de abarcar senão os itens que
		// ainda não se sabe se estão ordenados.
		for (int i = 0; i != unsorted - 1; i++)
			// Sempre que se encontra um par de itens fora de ordem,
			// troca-se os seus valores, o que leva os itens maiores
			// a «flutuarem» até encontrarem uma «bolha» maior.
			if (items[i] > items[i + 1])
				swap(length, items, i, i + 1);

	// Retornamos devolvendo `false`, i.e., assinalando o sucesso da
	// ordenação.
	return false;
}

// ### Ordenação por bolha ou _bubble sort_ (com contagem de operações)
bool bubble_sort_and_count(const int length, double items[length],
			struct algorithm_counts* counts)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || counts != NULL);

	if (length <= 1)
		return false;

	for (int unsorted = length; unsorted != 1; unsorted--)
		for (int i = 0; i != unsorted - 1; i++) {
			counts->comparisons++;
			if (items[i] > items[i + 1])
				swap_and_count(length, items, i, i + 1, counts);
		}

	return false;
}

// ### Ordenação por selecção ou _selection sort_
bool selection_sort(const int length, double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	// _Arrays_ vazios ou com apenas um item estão sempre ordenados, pelo
	// que podemos terminar a execução da rotina.
	if (length <= 1)
		return false;

	// A variável `sorted` guarda o número de itens que já se sabe estarem
	// ordenados e na sua posição definitiva. Inicialmente tem 0 como valor,
	// pois ainda não se procedeu a qualquer troca. Após cada iteração do
	// ciclo interior, o menor dos itens que ainda não se sabe se estão
	// ordenados e na sua posição definitiva é trocado com o item mais à
	// esquerda dos itens que não se sabe se estão ordenados e na sua
	// posição definitiva, ficando por isso na sua posição definitiva, pelo
	// que o valor da variável `sorted` é incrementado. Conceptualmente, o
	// _array_ está dividido em dois segmentos. Os itens que se sabe estarem
	// ordenados e na posição definitiva concentram-se num segmento com
	// `sorted` itens que se encontra no início do _array_. Os itens que
	// ainda não se sabe se estão ordenados e na posição definitiva
	// concentram-se num segmento com `length` - `sorted` itens que se
	// encontra no fim do _array_.
	for (int sorted = 0; sorted != length - 1; sorted++) {
		// O ciclo interior procura o índice do menor dos itens que
		// ainda não se sabe se estão ordenados e na posição definitiva.
		int i_of_smallest = sorted;
		for (int i = sorted + 1; i != length; i++)
			if (items[i] < items[i_of_smallest])
				i_of_smallest = i;
		// A troca do valor do menor item encontrado e do primeiro dos
		// itens que ainda não se sabe se estão ordenados e na posição
		// definitiva só se realiza _se não se tratar do mesmo item_.
		if (i_of_smallest != sorted)
			swap(length, items, sorted, i_of_smallest);
	}

	// Retornamos devolvendo `false`, i.e., assinalando o sucesso da
	// ordenação.
	return false;
}

// ### Ordenação por selecção ou _selection sort_ (com contagem de operações)
bool selection_sort_and_count(const int length, double items[length],
			struct algorithm_counts* counts)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || counts != NULL);

	if (length <= 1)
		return false;

	for (int sorted = 0;
		sorted != length - 1;
		sorted++) {
		int i_of_smallest = sorted;
		for (int i = sorted + 1; i != length; i++) {
			counts->comparisons++;
			if (items[i] < items[i_of_smallest])
				i_of_smallest = i;
		}
		if (i_of_smallest != sorted)
			swap_and_count(length, items,
					sorted, i_of_smallest, counts);
	}

	return false;
}

// ### Ordenação por inserção ou _insertion sort_
bool insertion_sort(const int length, double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	// _Arrays_ vazios ou com apenas um item estão sempre ordenados, pelo
	// que podemos terminar a execução da rotina.
	if (length <= 1)
		return false;

	// A variável `sorted` guarda o número de itens que já se sabe estarem
	// ordenados embora não necessariamente na sua posição definitiva.
	// Inicialmente tem 1 como valor, pois, apesar de ainda não se ter
	// procedido a qualquer alteração no _array_, o primeiro item do _array_
	// está ordenado em relação a sim mesmo, embora possa não estar na sua
	// posição definitiva. Após cada iteração do ciclo interior, o mais à
	// esquerda dos itens que ainda não se sabe se estão ordenados é
	// inserido na posição correcta entre os itens que já estão ordenados,
	// pelo que o valor da variável `sorted` é incrementado.
	// Conceptualmente, o _array_ está dividido em dois segmentos. Os itens
	// que se sabe estarem ordenados mas não necessariamente na sua posição
	// definitiva concentram-se num segmento com `sorted` itens que se
	// encontra no início do _array_. Os itens que ainda não se sabe se
	// estão ordenados concentram-se num segmento com `length` - `sorted`
	// itens que se encontra no fim do _array_.
	for (int sorted = 1; sorted != length; sorted++) {
		// Guardamos o valor do mais à esquerda dos itens que se ainda
		// não se sabe se já estão ordenados.
		const double item_to_insert = items[sorted];
		// Percorrem-se os itens já ordenados à procura do local onde o
		// valor que se guardou deve ser inserido, deslocando-se os
		// itens para a direita no _array_ à medida que a procura
		// decorre.
		int i = sorted;
		while (i != 0 && item_to_insert < items[i - 1]) {
			items[i] = items[i - 1];
			i--;
		}
		// Insere-se o valor guardado na sua posição definitiva, mas
		// apenas se esta for diferente da sua posição original.
		if (i != sorted)
			items[i] = item_to_insert;
	}

	// Retornamos devolvendo `false`, i.e., assinalando o sucesso da
	// ordenação.
	return false;
}

// ### Ordenação por inserção ou _insertion sort_ (com contagem de operações)
bool insertion_sort_and_count(const int length, double items[length],
			struct algorithm_counts* counts)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || counts != NULL);

	if (length <= 1)
		return false;

	for (int sorted = 1; sorted != length; sorted++) {
		counts->copies++;
		const double item_to_insert = items[sorted];
		int i = sorted;
		while (i != 0 && item_to_insert < items[i - 1]) {
			counts->comparisons++;
			counts->copies++;
			items[i] = items[i - 1];
			i--;
		}
		if (i != 0)
			counts->comparisons++;
		if (i != sorted) {
			counts->copies++;
			items[i] = item_to_insert;
		}
	}

	return false;
}

// ### Ordenação de Shell ou _Shell sort_
bool shell_sort(const int length, double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	// _Arrays_ vazios ou com apenas um item estão sempre ordenados, pelo
	// que podemos terminar a execução da rotina.
	if (length <= 1)
		return false;

	// Os incrementos decrescentes a usar pertencem à sucessão 1, 4, 13, 40,
	// 121, etc. Este ciclo procura o valor inicial desses incrementos. Ver
	// Algorithms, de Robert Sedgewick e Kevin Wayne (4.ª edição), pág. 259.
	int step = 1;
	while (step < length / 3)
		step = 3 * step + 1;

	// Percorremos cada incremento da sucessão até ao incremento 1.
	while (step >= 1) {
		// Executa-se o algoritmo de ordenação por inserção a sub-
		// _arrays_ entremeados obtidos percorrendo o _array_ em saltos
		// dados pelo incremento.
		for (int i = step; i != length; i++) {
			const double item_to_insert = items[i];
			int j = i;
			while (j >= step && item_to_insert < items[j - step]) {
				items[j] = items[j - step];
				j -= step;
			}
			if (j != i)
				items[j] = item_to_insert;
		}
		step /= 3;
	}

	// Retornamos devolvendo `false`, i.e., assinalando o sucesso da
	// ordenação.
	return false;
}

// ### Ordenação de Shell ou _Shell sort_ (com contagem de operações)
bool shell_sort_and_count(const int length, double items[length],
			struct algorithm_counts* counts)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || counts != NULL);

	if (length <= 1)
		return false;

	int step = 1;
	while (step < length / 3)
		step = 3 * step + 1;

	while (step >= 1) {
		for (int i = step; i != length; i++) {
			counts->copies++;
			const double item_to_insert = items[i];
			int j = i;
			while (j >= step && item_to_insert < items[j - step]) {
				counts->comparisons++;
				counts->copies++;
				items[j] = items[j - step];
				j -= step;
			}
			if (j >= step)
				counts->comparisons++;
			if (j != i) {
				counts->copies++;
				items[j] = item_to_insert;
			}
		}
		step /= 3;
	}

	return false;
}

// ### Ordenação rápida ou _quicksort_
//
// A ordenação rápida é implementada recorrendo a um procedimento recursivo de
// ordenação de um segmento de um _array_ e a uma rotina que invoca o
// procedimento especificando o _array_ completo como segmento a ordenar.
  
// #### Procedimento recursivo auxiliar de ordenação rápida
//
// Procedimento auxiliar que implementa o algoritmo de ordenação rápida sobre o
// segmento do _array_ `items` (cujo comprimento é `length`) com início no
// índice `first` e fim no índice `last`. Este procedimento é recursivo.
static void quicksort_segment(const int length, double items[length],
			const int first, const int last)
{
	// ##### Verificação das pré-condições
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(0 <= first);
	assert(last < length);

	// ##### Verificação dos casos especiais
	//
	// Se o segmento tem um número de itens inferior a dois, não é
	// necessário fazer nada: está ordenado por natureza.
	if (first >= last)
		return;

	// ##### Particionamento do segmento
	//
	// Seleccionamos um _pivot_ e particionamos o segmento de modo a colocar
	// o _pivot_ no seu lugar definitivo, com todos os itens do segmento à
	// sua esquerda com valor inferior ou igual ao do _pivot_ e todos os
	// itens do segmento à sua direita com valor superior ou igual. O
	// segmento fica, assim, particionado em três partes: (a) sub-segmento
	// esquerdo, por ordenar, (b) _pivot_ e (c) sub-segmento direito. Depois
	// deste particionamento, a ordenação total consegue-se ordenando de
	// forma independente os sub-segmentos esquerdo e direito, usando
	// exactamente o mesmo algoritmo.
  
	// O _pivot_ será o primeiro item do segmento. Para simplificar o ciclo
	// em `i` do particionamento, em que se procura um item maior ou igual
	// ao _pivot_ a partir da esquerda, convém garantir que o último item do
	// segmento não seja inferior ao _pivot_, pois evita-se ter de verificar
	// se o valor de `i` ultrapassa o valor de `last`. Para o garantir,
	// compara-se os dois itens extremos do segmento, trocando o seu valor
	// de modo a garantir que o primeiro é menor ou igual ao último. Dessa
	// forma, o _pivot_ funcionará como uma _sentinela_ para o ciclo em `j`
	// e o último item do segmento funcionará como uma _sentinela_ para o
	// ciclo em `i`.
	if (items[first] > items[last])
		swap(length, items, first, last);
	const double pivot = items[first];

	// Inicializamos a variável `i`, que percorrerá o segmento a partir da
	// esquerda, «saltando» sobre o _pivot_. Note que a primeira operação
	// realizada no ciclo em `i` é uma incrementação, pelo que se salta de
	// facto o _pivot_, apesar de se inicializar `i` com `first`.
	int i = first;
	// Inicializamos a variável `j`, que percorrerá o segmento a partir da
	// direita. Note que a primeira operação realizada no ciclo em `j` é uma
	// decrementação, pelo que é necessário inicializar `j` com `last` + 1,
	// e não simplesmente com `last`.
	int j = last + 1;

	// O ciclo principal do particionamento serve para ir procurando pares
	// de itens a trocar, um a partir da esquerda, outro a partir da
	// direita. O passo do ciclo tem de ser executado pelo menos uma vez,
	// pelo que é apropriado usar um ciclo `do while`.
	do {
		// Procura-se o primeiro candidato à troca a partir da esquerda.
		do
			i++;
		while(items[i] < pivot);

		// Procura-se o primeiro candidato à troca a partir da direita.
		do
			j--;
		while(pivot < items[j]);

		// Se os índices não se cruzaram, é necessário trocar os valores
		// dos respectivos itens e continuar o particionamento.
		if (i < j)
			swap(length, items, i, j);
	} while(i < j);
	// O particionamento termina quando os índices `i` e `j` se cruzam.
	// Quando isso acontece, o índice `j` é o índice do primeiro item a
	// partir da direita que tem um valor menor ou igual ao _pivot_, podendo
	// por isso ser usado como posição definitiva do _pivot_. Se o valor de
	// `j` for igual a `first`, então o primeiro sub-segmento está vazio e o
	// _pivot_ está na sua posição correcta, pelo não é necessário trocar a
	// sua posição nem proceder a qualquer ordenação do sub-segmento
	// esquerdo.
	if(j != first) {
		// Trocamos os valores dos itens `first` e `j`, para que o
		// _pivot_ fique na posição definitiva, ou seja, na posição `j`.
		swap(length, items, first, j);

		// ##### Invocação recursiva do algoritmo
		//
		// Feito o particionamento, aplica-se recursivamente o mesmo
		// algoritmo a cada um dos sub-segmentos.
  
		// Invocação do mesmo algoritmo para ordenação do sub-segmento
		// esquerdo, entre `first` e `j` - 1. (O _pivot_ está na posição
		// `j`.)
		quicksort_segment(length, items, first, j - 1);
	}
	// Invocação do mesmo algoritmo para ordenação do sub-segmento direito,
	// entre `j` + 1 e `last`. (O _pivot_ está na posição `j`.)
	quicksort_segment(length, items, j + 1, last);
}

// #### Rotina de ordenação rápida
//
// Esta rotina não é recursiva, recorrendo ao procedimento recursivo definido
// acima para efectuar a ordenação rápida.
bool quicksort(const int length, double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	// Invocamos o procedimento recursivo de ordenação de um segmento do
	// _array_ passando-lhe como posições extremas do segmento a ordenar os
	// valores 0 e `length` - 1, ou seja, indicando que pretendemos ordenar
	// o _array_ no seu todo.
	quicksort_segment(length, items, 0, length - 1);

	// Retornamos devolvendo `false`, i.e., assinalando o sucesso da
	// ordenação.
	return false;
}

// ### Ordenação rápida ou _quicksort_ (com contagem de operações)

static void quicksort_segment_and_count(const int length, double items[length],
					const int first, const int last,
					struct algorithm_counts* counts)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || counts != NULL);
	assert(0 <= first);
	assert(last < length);

	if (first >= last)
		return;

	int i = first;
	int j = last + 1;
	counts->comparisons++;
	if (items[first] > items[last])
		swap_and_count(length, items, first, last, counts);
	const double pivot = items[first];
	do {
		do {
			i++;
			counts->comparisons++;
		} while(items[i] < pivot);
		do {
			j--;
			counts->comparisons++;
		} while(pivot < items[j]);
		if (i < j)
			swap_and_count(length, items, i, j, counts);
	} while(i < j);
	if(j != first) {
		swap_and_count(length, items, first, j, counts);
		quicksort_segment_and_count(length, items, first, j - 1, counts);
	}
	quicksort_segment_and_count(length, items, j + 1, last, counts);
}

bool quicksort_and_count(const int length, double items[length],
			struct algorithm_counts* counts)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || counts != NULL);

	quicksort_segment_and_count(length, items, 0, length - 1, counts);

	return false;
}

// ### Ordenação por fusão ou _merge sort_
//
// A ordenação por fusão é implementada recorrendo a:
//
// - um procedimento auxiliar `merge_sort_segment()`, recursivo, que ordena
//   um segmento de _array_ recorrendo a um _array_ auxiliar com a mesma
//   dimensão do _array_ a ordenar,
// - um procedimento auxiliar `merge()`, não recursivo, que funde num único
//   segmento ordenado de _array_  dois sub-segmentos ordenados e adjacentes de
//   _array_, e  
// - uma rotina `merge_sort()`, não recursiva, que constrói um _array_ auxiliar
//   e invoca o procedimento auxiliar `merge_sort_segment()` passando-lhe o
//   _array_ a ordenar e o _array_ auxiliar e especificando o array completo
//   como segmento a ordenar.
  
// #### Procedimento não recursivo auxiliar de fusão de segmentos
  
// Procedimento auxiliar, não recursivo, que funde num único segmento ordenado
// os dois sub-segmentos adjacentes do _array_ `items` com comprimento `length`
// com início no índice `left` e fim no índice `middle`, o primeiro, e com
// início no índice `middle` + 1 e fim no índice `right`, o segundo. A fusão é
// feita recorrendo a um _array_ auxiliar `temporary`.
static void merge(const int length, double items[length],
		double temporary[length],
		const int left, const int middle, const int right)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || temporary != NULL);
	assert(0 <= left && left < length);
	assert(0 <= right && right < length);
	assert(left <= middle && middle < right);

	// Note que, recorrendo a apenas uma comparação adicional por fusão,
	// podemos melhorar substancialmente a eficiência deste algoritmo
	// _quando o array a ordenar já está ordenado_. Basta acrescentar a
	// seguinte instrução condicional no início do procedimento:
	//
	// ```C
	// if (items[middle] <= items[middle + 1])
	//     return;
	// ```
  
	// ##### Fusão dos sub-segmentos
	//
	// A primeira fase da fusão ocorre enquanto não se esgotou nenhum dos
	// dois segmentos a fundir. Durante este ciclo, os itens são copiados
	// dos dois segmentos a fundir para o segmento resultante da fusão _mas
	// no array auxiliar_. Usamos três índices para o efeito.
  
	// O índice `i` percorre o primeiro sub-segmento a fundir, começando por
	// isso em `left`.
	int i = left;
	// O índice `j` percorre o segundo sub-segmento a fundir, começando por
	// isso em `middle` + 1.
	int j = middle + 1;
	// O índice `k` percorre o segmento resultante da fusão, começando por
	// isso em `left`, tal como `i`. No entanto, note-se que os valores são
	// copiados para o segmento resultante da fusão _no array auxiliar_.
	// Só depois são copiados de volta para o _array_ a ordenar.
	int k = left;
	// O ciclo decorre enquanto nenhum dos sub-segmentos se esgotar.
	for (; i <= middle && j <= right; k++)
		// O valor a colocar na posição `k` do _array_ auxiliar é o
		// menor dos valores indexados por `i` e por `j`.
		if (items[i] <= items[j])
			// Tendo-se copiado o item em `i` do primeiro sub-
			// segmento, incrementamos valor de `i`.
			temporary[k] = items[i++];
		else
			// Tendo-se copiado o item em `j` do segundo sub-
			// segmento, incrementamos valor de `j`.
			temporary[k] = items[j++];

	// ##### Cópia dos itens remanescentes do primeiro sub-segmento
  
	// Quando o ciclo acima termina, pelo menos um dos sub-segmentos está
	// esgotado. Este primeiro ciclo lida com os itens do primeiro segmento
	// que não chegaram a ser copiados para o _array_ temporário. Se o
	// primeiro segmento se tiver esgotado no ciclo anterior, então não terá
	// qualquer efeito. Para evitar a realização de duas cópias dos valores
	// destes itens, primeiro para o _array_ auxiliar, depois para o _array_
	// a ordenar, copiamos estes itens para a sua posição no _array_ a
	// ordenar, a partir da posição dada por `k`.
	for (int m = k; i <= middle; i++, m++)
		items[m] = items[i];

	// Da mesma forma, o segundo sub-segmento do _array_ pode não ter sido
	// esgotado no ciclo original. Se isso aconteceu, então os itens desse
	// sub-segmento _já estão na sua posição definitiva_.
  
	// ##### Recolocação dos itens fundidos no _array_ a ordenar
  
	// Finalmente, é necessário copiar para o _array_ a ordenar os itens
	// colocados no _array_ auxiliar durante o primeiro ciclo, de fusão, que
	// decorreu enquanto nenhum dos sub-segmentos se esgotou.
	for (int i = left; i < k; i++)
		items[i] = temporary[i];
}

// #### Procedimento recursivo auxiliar de ordenação por fusão
  
// Procedimento auxiliar que implementa o algoritmo de ordenação por fusão sobre
// o segmento do _array_ `items` (cujo comprimento é `length`) com início no
// índice `left` e fim no índice `right`, recorrendo ao _array_ auxiliar
// `temporary` com o mesmo comprimento do _array_ `items`. Este procedimento é
// recursivo.
static void merge_sort_segment(const int length,
				double items[length], double temporary[length],
				const int left, const int right)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || temporary != NULL);
	assert(length == 0 || left <= right);
	assert(0 <= left);
	assert(right < length);

	// Se o segmento a ordenar tem comprimento inferior a 2, então está já
	// ordenado por natureza, pelo que terminamos imediatamente o
	// procedimento.
	if (left >= right)
		return;

	// Calculamos o ponto médio do segmento em ordenação, dividindo-o em
	// dois sub-segmentos: o primeiro sub-segmento com índices entre `left`
	// e `middle` e o segundo sub-segmento com índices entre `middle` + 1 e
	// `right`. Se o segmento tiver um comprimento par, então os dois sub-
	// segmentos terão exactamente metade desse comprimento. Se o
	// comprimento do segmento for ímpar, então o primeiro sub-segmento terá
	// um comprimento maior em uma unidade que o segundo sub-segmento.
	int middle = (left + right) / 2;

	// Aplicando uma estratégia _dividir para conquistar_, aplica-se o mesmo
	// procedimento, de forma recursiva, para ordenar _separadamente_ cada
	// um dos sub-segmentos adjacentes obtidos.
	merge_sort_segment(length, items, temporary, left, middle);
	merge_sort_segment(length, items, temporary, middle + 1, right);

	// Neste ponto os dois sub-segmentos adjacentes já estão ordenados, pelo
	// que podemos fundi-los num único segmento recorrendo ao procedimento
	// de fusão.
	merge(length, items, temporary, left, middle, right);
}

// #### Rotina de ordenação por fusão
  
// Esta rotina não é recursiva, recorrendo ao procedimento recursivo definido
// acima para efectuar a ordenação por fusão.
bool merge_sort(const int length, double items[length])
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);

	// _Arrays_ vazios ou com apenas um item estão sempre ordenados, pelo
	// que podemos terminar a execução da rotina.
	if (length <= 1)
		return false;

	// Construímos um _array_ auxiliar que será usado durante a fusão.
	double *const temporary = new_double_array_of(length);

	// Verificamos a construção do novo _array_ teve sucesso.
	if (temporary == NULL)
		return true;

	// Invocamos o procedimento recursivo de ordenação de um segmento do
	// _array_ passando-lhe como posições extremas do segmento a ordenar os
	// valores 0 e `length` - 1, ou seja, indicando que pretendemos ordenar
	// o _array_ no seu todo.
	merge_sort_segment(length, items, temporary, 0, length - 1);

	// Libertamos o _array_ auxiliar.
	free(temporary);

	// Retornamos devolvendo `false`, i.e., assinalando o sucesso da
	// ordenação.
	return false;
}

// ### Ordenação por fusão ou _merge sort_ (com contagem de operações)

static void merge_and_count(const int length, double items[length],
			double temporary[length],
			const int left, const int middle, const int right,
			struct algorithm_counts* counts)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || temporary != NULL);
	assert(length == 0 || counts != NULL);
	assert(0 <= left && left < length);
	assert(0 <= right && right < length);
	assert(left <= middle && middle < right);

	int i = left;
	int j = middle + 1;
	int k = left;
	while (i <= middle && j <= right) {
		counts->comparisons++;
		counts->copies++;
		if (items[i] <= items[j])
			temporary[k++] = items[i++];
		else
			temporary[k++] = items[j++];
	}

	while (i <= middle) {
		counts->copies++;
		temporary[k++] = items[i++];
	}

	for (int i = left; i < j; i++) {
		counts->copies++;
		items[i] = temporary[i];
	}
}

static void merge_sort_segment_and_count(const int length,
					double items[length],
					double temporary[length],
					const int left, const int right,
					struct algorithm_counts* counts)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || temporary != NULL);
	assert(length == 0 || counts != NULL);
	assert(length == 0 || left <= right);
	assert(0 <= left);
	assert(right < length);

	if (left >= right)
		return;

	int middle = (right + left) / 2;

	merge_sort_segment_and_count(length, items, temporary,
				left, middle, counts);
	merge_sort_segment_and_count(length, items, temporary,
				middle + 1, right, counts);

	merge_and_count(length, items, temporary, left, middle, right, counts);
}

bool merge_sort_and_count(const int length, double items[length],
			struct algorithm_counts* counts)
{
	assert(length >= 0);
	assert(length == 0 || items != NULL);
	assert(length == 0 || counts != NULL);

	if (length <= 1)
		return false;

	double *const temporary = new_double_array_of(length);

	if (temporary == NULL)
		return true;

	merge_sort_segment_and_count(length, items, temporary, 0, length - 1,
				counts);

	free(temporary);

	return false;
}
