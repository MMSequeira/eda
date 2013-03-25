// O básico sobre os _arrays_
// ==========================
//
// O que são os _arrays_
// ---------------------
//
// Os _arrays_ são uma das formas de agregar dados em C. Nos _arrays_ os dados,
// a que chamamos «itens», são todos do mesmo tipo. Estes dados estão
// organizados numa sequência com um comprimento fixo. Por exemplo,
//
// ```C
//   int array[4];
// ```
// define um novo _array_ com exactamente quatro inteiros.
//
// Inicalização de _arrays_
// ------------------------
//
// ### Inicialização por omissão 
//
// Tal como acontece no caso de variáveis dos tipos básicos da linguagem, por
// omissão o C _não_ inicializa os itens de um _array_ (desde que seja um
// _array_ automático, pois se for estático todos os itens são inicializados com
// um valor nulo). Ou seja, estes começam a sua vida com valores que, do ponto
// de vista do programador, são puro lixo, mesmo que provavelmente estes valores
// consistam simplesmente numa interpretação do padrão de _bits_ que se encontra
// na memória alocada para esses itens ou variáveis.
//
// ### Inicialização explícita
//
// Os _arrays_ podem ser inicializados explicitamente através de uma lista
// de inicializadores:
//
// ```C
//   int array[4] = {0, 1, 2};
// ```
//
// Neste caso omitimos o valor inicial do quarto item do _array_. Quando isto
// acontece, o compilador do C encarrega-se de gerar código máquina que
// inicializa os itens em falta com valores nulos. Podemos, por isso, usar um
// truque simpático para inicializar todos os itens dos _arrays_ do C com o
// valor zero (no entanto, a norma que especifica o C11 não é clara quanto à
// validade de usar uma lista de inicialização vazia...):
//
// ```C
//   int array[4] = {};
// ```
//
// Quando se fornece uma lista de inicialização, é possível omitir a
// dimensão dos _arrays_. Nesse caso, o _array_ terá como dimensão o número
// de valores colocado entre chavetas. Por exemplo, o código
//
// ```C
//   int array[] = {0, 1, 2};
// ```
//
// define um _array_ com exactamente três itens.

// Inclusão de ficheiros de cabeçalho para utilização do procedimento
// printf() e para poder usar a _macro_ `EXIT_SUCCESS`.
#include <stdio.h>
#include <stdlib.h>

// Incluímos o ficheiro de cabeçalho `array_utils.h`, pois contém a declaração
// do procedimento `void print(int number_of_items, int
// items[number_of_items])`, usado mais abaixo. A inclusão está a ser feita
// encerrando o nome do ficheiro entre aspas, e não entre parênteses agudos.
// Isso faz com que o compilador procure o ficheiro não apenas nos locais padrão
// habituais (e.g., `/usr/include`) mas também no próprio projecto em que nos
// encontramos. Neste caso o ficheiro está no projecto Code::Blocks
// `array_utils`, cujo propósito é a criação de uma biblioteca de utilitários
// para lidar com _arrays_. Note que não basta que este ficheiro de cabeçalho,
// contendo o _protótipo_, esteja disponível para inclusão durante o processo de
// construção (mais precisamente durante o pré-processamento): é necessário que
// esteja também disponível uma biblioteca ou um ficheiro objecto com o
// resultado da compilação do ou dos ficheiros de implementação correspondentes.
// Essa biblioteca ou ficheiro objecto será _fundido_ com os restantes ficheiros
// objecto e bibliotecas durante o passo da _fusão_ do código.
#include "array_utils.h"

// Definição de uma função
// =======================
//
// Definimos uma função que devolve a média dos itens da matriz passada como
// argumento. Uma definição de uma rotina consiste num _cabeçalho_, onde se
// caracteriza a interface da rotina, e num _corpo_, onde se coloca a
// _implementação_ da rotina. Neste caso temos uma _definição_, e não uma
// simples _declaração_, pois incluímos o corpo da função. Todas as definições
// são também declarações, mas nem todas as declarações são definições. Uma
// declaração simples, sem indicação da implementação, inclui apenas o cabeçalho
// da rotina seguido de um ponto e vírgula. O ficheiro
// [`array_utils.h`](array_utils.html) contém apenas a declaração da função.

// ### Documentação e cabeçalho da função
//
// O _cabeçalho_ de uma rotina declara a sua existência e especifica a sua forma
// de utilização, mas não especifica totalmente a _interface_ da função. A
// interface completa de uma rotina inclui informação mais pormenorizada acerca
// dos objectivos da rotina, acerca do significado dos parâmetros, etc., mas,
// sobretudo, estabelece um contrato claro entre o _programador produtor_ da
// rotina, i.e., o ou os programadores que a implementam e mantêm, e o
// _programador consumidor ou cliente_ da rotina, i.e., o ou os programadores
// que a usam no seu código. O C não suporta directamente a especificação da
// interface completa da rotina. Por isso, essa especificação é feita recorrendo
// a um _comentário de documentação_.

// #### Documentação
//
// O cabeçalho é precedido de um _comentário de documentação_ que indica
// claramente qual o contrato desta função. Usamos aqui o formato de
// documentação [Doxygen](doxygen.org).
/** \brief Returns the average of the items of a given array.
 *
 * \param number_of_items The number of items of the array `items` to consider.
 * \param items The array (or rather, a pointer to its first item) whose
 * items will be averaged.
 * \return the average of the first `number_of_items` items of array `items`.
 *
 * This function calculates and returns the average of the first
 * `number_of_items` items of array `items`.
 */
//
// #### Cabeçalho
//
// Este cabeçalho inclui a seguinte informação:
//
// - Nome da função &ndash; O nome da função deve ser tão explícito e claro
//   quanto possível. Pense numa possível utilização da função para chegar a um
//   bom nome. Por exemplo, suponha-se que existe um _array_ chamado
//   `student_grades` com a lista das notas de um dado aluno e se pretende saber
//   se a sua média ultrapassa os 15 valores. O código a escrever seria o que se
//   segue, que é legível quase como se se tratasse de inglês:
//
// ```C
// if (average_of(student_grades) > 15.0)
//         ...
// ```
//
// - Tipo do valor devolvido &ndash; !!!!!!!!!!!!!!!!!!!
double average_of(int number_of_items, int items[number_of_items])
//double average_of(int* items)
{
	double sum = 0.0;

	for (int i = 0; i != number_of_items; i++)
		sum += items[i];

	return sum / 4;
}

int main(void)
{
//	printf("How many students? ");
//	int number_of_students;
//	scanf("%d", &number_of_students);
//
//	int student_ages[number_of_students];
	int student_ages[] = {23, 24, 25, 26};
	const int number_of_students =
		sizeof(student_ages) / sizeof(int);

	print(number_of_students, student_ages);

	for (int i = 0; i != number_of_students; i++)
		printf("%d\n", student_ages[i]);

	printf("The average age is %g.\n",
		average_of(number_of_students, student_ages));

	return EXIT_SUCCESS;
}
