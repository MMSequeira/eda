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

// Inclusão de ficheiros de interface
// -----------------------------------
//
// Incluímos os vários ficheiro de interface necessários:
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

// Note como classificamos `length` como `const`. Esta prática ajuda o
// compilador a detectar os nossos próprios erros. Ao afirmarmos explicitamente
// que não tencionamos alterar um parâmetro, permitimos que o compilador detecte
// alterações realizadas por engano. Seguimos esta prática em todo o código
// deste projecto.
double *new_double_array_of(const long length)
{
	assert(length >= 0L);

	return malloc(length * sizeof(double));
}

double *resize_double_array_to(double *const items, const long new_length)
{
	assert(new_length >= 0L);

	return realloc(items, new_length * sizeof(double));
}

double *read_double_array_from(const char *const file_name, long *const length)
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

	// O _array_ onde iremos guardando os itens lidos tem de ir crescendo à
	// medida que a leitura prossegue. Em cada instante, o _array_ terá como
	// capacidade o valor guardado nesta variável. O número de itens já
	// lidos e guardados no _array_ será sempre inferior ou igual à sua
	// capacidade.
	long capacity = 32L;

	// Criamos o _array_ com a capacidade definida inicialmente.
	double *items = new_double_array_of(capacity);

	// No caso de não se conseguir criar o novo _array_ dinâmico, fechamos o
	// canal aberto para o ficheiro em leitura e retornamos devolvendo o
	// valor especial `NULL`, de modo a assinalar o erro.
	if (items == NULL) {
		fclose(file);
		return NULL;
	}

	// O ciclo de leitura é feito recorrendo a duas variáveis locais. A
	// primeira, `i`, indica em cada momento, e simultaneamente, quantos
	// itens já foram lidos e o índice do item do _array_ onde será guardado
	// o próximo valor lido do ficheiro. A segunda variável é usada para ler
	// cada um dos itens. Em caso de sucesso na leitura, o valor contido
	// neste variável será atribuído ao item apropriado do _array_.
	long i = 0L;
	double item;
	// A guarda do ciclo inclui a própria operação de leitura. Esta forma de
	// escrever o ciclo é idiomática do C e seria considerada uma má prática
	// em qualquer outra linguagem. Fazemos a leitura usando a usual rotina
	// `fscanf()`, recorrendo à especificação de conversão `%lg`, onde a
	// utilização de `l` é necessária por se tratar de `doubles`. A leitura
	// é realizada para a variável `item`, pelo que passamos o seu endereço
	// à rotina `fscanf()`. Se a leitura tiver sucesso, a rotina devolve o
	// valor 1, pois terá sido atribuído exactamente um valor, nomeadamente
	// o valor lido do ficheiro e guardado na variável `item`.
	while (fscanf(file, "%lg", &item) == 1) {
		// Se o número de itens lidos com sucesso e guardados no _array_
		// for igual à capacidade do _array_, então esta encontra-se
		// esgotada. Sendo necessário aumentar a capacidade do _array_,
		// pode-se demonstrar que uma forma eficiente de o fazer é
		// duplicá-la, pois leva a uma número médio de cópias por item
		// do _array_ que é constante e pequeno. Note que o valor da
		// variável `capacidade` é aumentado na mesma instrução em que
		// se aumenta a capacidade do _array_, pelo que essa instrução
		// terá dois efeitos distintos. Mais uma vez, trata-se de código
		// muito discutível, mas idiomático na linguagem C.
		if (i == capacity) {
			double *new_items =
				resize_double_array_to(items, capacity *= 2L);
			if (new_items == NULL) {
				fclose(file);
				free(items);
				return NULL;
			}
			items = new_items;
		}
		// Atribuímos o valor lido ao item do _array_ com índice `i` _e
		// incrementamos o próprio `i`_! O valor de `i` usado na
		// indexação é o valor original de `i`, antes da incrementação.
		// Trata-se, outra vez, de código muito discutível, mas
		// idiomático na linguagem C.
		items[i++] = item;
	}

	// Finda a leitura, a variável `i` contém o número de itens lidos e
	// guardados no _array_. Guardamos o seu valor na variável apontada por
	// `length`.
	*length = i;

	// Se necessário, ajustamos a capacidade do _array_ de modo a
	// corresponder exactamente ao número de itens lidos, de modo a garantir
	// que não há desperdício de memória.
	if (*length != capacity)
		items = resize_double_array_to(items, *length);

	// Fechamos o canal de entrada.
	fclose(file);

	// Retornamos, devolvendo o endereço do primeiro item do _array_
	// dinâmico criado, que contém os valores lidos do ficheiro.
	return items;
}

void copy_double_array(const long length,
		double copy[length], const double original[length])
{
	assert(length >= 0L);
	assert(length == 0L || copy != NULL);
	assert(length == 0L || original != NULL);

	for (long i = 0L; i != length; i++)
		copy[i] = original[i];
}

bool double_arrays_equal(const long length,
			const double first[length], const double second[length])
{
	assert(length >= 0L);
	assert(length == 0L || first != NULL);
	assert(length == 0L || second != NULL);

	// Note a utilização de um ciclo com apenas um local de terminação.
	long i = 0L;
	while(i != length && first[i] == second[i])
		i++;
	return i == length;
}

// Esta função é usada durante a ordenação de _arrays_ de `double` realizada
// através do procedimento `qsort()` da biblioteca padrão do C. A utilização de
// ponteiros para `void` como tipo dos seus parâmetros é um requisito do
// procedimento `qsort()`, que, desta forma, é capaz de ordenar _arrays_ de
// itens de qualquer tipo. O procedimento `qsort()` requer que esta função
// devolva um valor inteiro que indica a relação de ordem entre o primeiro e o
// segundo argumento. Se o primeiro for superior ao segundo, o valor `int`
// devolvido deverá ser positivo. Se for igual, o valor devolvido deverá ser
// nulo. Se for menor, deverá devolver um valor negativo. Sendo esta função de
// utilidade restrita, optámos por lhe dar ligação local, usando para isso o
// qualificador `static`.
static int compare(const void *first_generic, const void *second_generic)
{
	// Os argumentos são ponteiros para os itens a comparar. Sendo o
	// procedimento `qsort()` genérico, os parâmetros correspondentes são do
	// tipo `void *`. Para aceder aos valores do tipo `double`, fazem-se
	// coerções para o tipo ponteiro para `double`.
	const double *first = first_generic;
	const double *second = second_generic;

	if (first < second)
		return -1;
	else if(first > second)
		return 1;
	else
		return 0;
}

double double_array_average(const long length, const double items[length])
{
	assert(length >= 0L);
	assert(length == 0L || items != NULL);

	double sum = 0.0;

	for (long i = 0L; i != length; i++)
		sum += items[i];

	return sum / length;
}

// Uma função auxiliar devolvendo o quadrado do valor recebido como argumento.
static double square_of(const double value)
{
	return value * value;
}

double double_array_stddev(const long length, const double items[length])
{
	assert(length >= 0L);
	assert(length == 0L || items != NULL);

	// Esta implementação é simples, mas ineficaz. Ver mais abaixo uma
	// implementação do cálculo do desvio padrão que não exige percorrer o
	// _array_ duas vezes.
	const double average = double_array_average(length, items);

	double sum = 0.0;

	for (long i = 0L; i != length; i++)
		sum += square_of(items[i] - average);

	return sqrt(sum / length);
}

// Usamos uma forma de cálculo muito ineficaz: ordenar o _array_ de modo
// a obter a mediana através do ou dos valores centrais. Há formas bem
// mais eficazes de calcular a mediana. Nomeadamente, pode-se usar uma
// versão modificada do algoritmo de ordenação rápida que não se
// preocupa em ordenar o _array_, mas apenas em realizar
// particionamentos sucessivos até determinar o valor do ou dos itens
// centrais do _array_, que não precisa por isso de ser totalmente
// ordenado.
double double_array_median(const long length, const double items[length])
{
	assert(length >= 0L);
	assert(length == 0L || items != NULL);

	// Primeiro lidamos com o caso especial da mediana de zero itens.
	if (length == 0L)
		return NAN;

	// Criamos um _array_ de trabalho que é uma cópia do _array_ original,
	// pois este não deve ser alterado.
	double work_items[length];
	copy_double_array(length, work_items, items);

	// Usamos o procedimento de ordenação genérico do C `qsort()`, que
	// utiliza o algoritmo de ordenação rápida, para ordenar o _array_ de
	// trabalho.
	qsort(work_items, length, sizeof(double), compare);

	// Se o _array_ tiver um número par de itens, a sua mediana é a média
	// aritmética dos valores dos dois itens mais próximos do meio do
	// _array_ ordenado. Se tiver um número ímpar de itens, então a mediana
	// é o valor do item central do _array_ ordenado.
	if (length % 2 == 0L)
		return (work_items[length / 2 - 1] + work_items[length / 2]) / 2;
	else
		return work_items[length / 2];
}

// Note que esta função está definida mesmo para zero itens, devolvendo infinito
// (+∞) nesse caso, pois o infinito é o elemento neutro da operação de obtenção do
// menor de dois operandos, da mesma forma que o zero (0) é o elemento neutro da
// operação de obtenção da soma de dois operandos.
double double_array_minimum(const long length, const double items[length])
{
	assert(length >= 0L);
	assert(length == 0L || items != NULL);

	double minimum = INFINITY;

	for (long i = 0L; i != length; i++)
		if (items[i] < minimum)
			minimum = items[i];

	return minimum;
}

// Note que esta função está definida mesmo para zero itens, devolvendo infinito
// negativo (-∞) nesse caso, pois o infinito negativo é o elemento neutro da
// operação de obtenção do maior de dois operandos, da mesma forma que o zero
// (0) é o elemento neutro da operação de obtenção da soma de dois operandos.
double double_array_maximum(const long length, const double items[length])
{
	assert(length > 0L);
	assert(length == 0L || items != NULL);

	double maximum = -INFINITY;

	for (long i = 0L; i != length; i++)
		if (items[i] > maximum)
			maximum = items[i];

	return maximum;
}

struct double_statistics double_array_statistics(const long length,
						const double items[length])
{
	assert(length >= 0L);
	assert(length == 0L || items != NULL);

	// Esta variável guarda os valores das estatísticas e será devolvida
	// quando a função retornar. Note a forma de inicialização dos campos da
	// estrutura.
	struct double_statistics statistics = {
		.average = NAN,
		.stddev = NAN,
		.median = NAN,
		.minimum = INFINITY,
		.maximum = -INFINITY
	};

	// Lidamos primeiro com o caso especial em que há zero itens apenas. O
	// valor inicial da variável `statistics` foi escolhido de modo a cobrir
	// este caso.
	if (length == 0L)
		return statistics;

	// Uma vez que se calculam as várias estatísticas numa única função,
	// podemos fazer algumas optimizações. Ainda assim, seria possível
	// melhorar francamente a forma de cálculo da mediana, como referido
	// anteriormente.
	double work_items[length];

	double sum = 0.0;
	double sum_of_squares = 0.0;

	for (long i = 0L; i != length; i++) {
		work_items[i] = items[i];
		sum += items[i];
		sum_of_squares += square_of(items[i]);
	}

	statistics.average = sum / length;
	statistics.stddev =
		sqrt(sum_of_squares / length - square_of(statistics.average));

	qsort(work_items, length, sizeof(double), compare);

	statistics.minimum = work_items[0];

	if (length % 2 == 0L)
		statistics.median =
			(work_items[length / 2 - 1] + work_items[length / 2]) / 2;
	else
		statistics.median = work_items[length / 2];

	statistics.maximum = work_items[length - 1];

	return statistics;
}
