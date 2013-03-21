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

// Tal como acontece no
// caso de variáveis dos tipos básicos da linguagem, por omissão o C _não_
// inicializa os itens de um _array_. Ou seja, estes começam a sua vida com
// valores que, do ponto de vista do programador, são puro lixo, mesmo que
// provavelmente estes valores consistam simplesmente numa interpretação do
// padrão de _bits_ que se encontra na memória alocada para esses itens ou
// variáveis.
//
// Os _arrays_ podem ser inicializados explicitamente através de uma lista de
// inicializadores:
//
// ```C
//   int array[4] = {0, 1, 2};
// ```
//
// Note-se que neste caso se omitiu o valor inicial do quarto item do _array_.
// Quando isso acontece, o compilador do C encarrega-se de gerar código máquina
// que inicializa os itens em falta com o valor 0 (zero). Pode-se, por isso,
// usar um truque simpático para inicializar todos os itens dos _arrays_ do C
// com o valor zero:
//
// ```C
//   int array[4] = {};
// ```
//
// Quando se fornece uma lista de inicialização, é possível omitir a dimensão
// dos _arrays_. Nesse caso, o _array_ terá como dimensão o número de valores
// colocado entre chavetas.

// Inclusão de ficheiros de cabeçalho para utilização do procedimento printf() e
// para poder usar a _macro_ `EXIT_SUCCESS`.
#include <stdio.h>
#include <stdlib.h>

// Inclui-se o ficheiro de cabeçalho `array_utils.h`, pois contém a declaração
// do procedimento `void print(int number_of_items, int
// items[number_of_items])`, usada mais abaixo. Note-se que a inclusão está a
// ser feita encerrando o nome do ficheiro entre aspas, e não entre parênteses
// agudos. Isso faz com que o compilador procure o ficheiro não apenas
// nos locais padrão habituais (e.g., `/usr/include`) mas também no próprio
// projecto em que nos encontramos. Neste caso o ficheiro está no projecto
// Code::Blocks `array_utils`. Note-se que não basta que este ficheiro de
// cabeçalho, contendo o _protótipo_, esteja disponível para inclusão durante o
// processo de contrução (mais precisamente durante o pré-processamento). É
// necessário que esteja também disponível uma biblioteca ou um ficheiro objecto
// com o resultado da compilação do código fonte correspondente. Essa biblioteca
// ou ficheiro objecto será _fundido_ com os restantes ficheiros objecto e
// bibliotecas durante o passo da _fusão_ do código.
#include "array_utils.h"

//
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
