// `fibonacci.c`
// =============
/**
 * \file fibonacci.c
 * \brief Illustrates possible implementations of the calculation of terms of
 * the Fibonacci sequence.
 *
 * Iterative and recursive implementations of the calculation of terms of
 * the Fibonacci sequence. These implementations are used to illustrate
 * iteration vs. recursion, and also to show how a naïve implementation of
 * recursion may lead to serious problems.
 */

// Coelhos, recursão e iteração
// ----------------------------
//
// Ofereceram ao Sr. Fibonacci um casal de coelhos, recém-nascidos, de um
// espécie curiosa: tornam-se férteis ao fim de um mês de vida, concebem logo
// que possível, têm uma gestação de exactamente um mês, cada ninhada consiste
// sempre num casalinho de coelhos. Nunca morrem. O Sr. Fibonacci preocupou-se:
// teria comida que chegue para os coelhos? Pôs-se a calcular a evolução do
// número de casais de coelhos ao longo do tempo:
//
// 0. No mês zero o Sr. Fibonacci vivia feliz, sem qualquer coelho. Mal
// calculava o seu destino...
//
// 1. No primeiro mês há um casal de coelhos inférteis.
//
// 2. No segundo mês há um casal de coelhos, já férteis e, claro está, com a
// coelha no início da gestação de mais um casalinho.
//
// 3. No terceiro mês há o casal de coelhos original, fértil, e já no início da
// gestação de mais um casalinho de coelhos. E há, claro está, um casal recém-
// nascido e, por isso, infértil. Ou seja, há dois casais de coelhos, um fértil
// e outro infértil.
//
// 4. No quarto mês há os dois casais do mês anterior, já férteis, adicionados
// de um casal recém-nascido, resultado do acasalamento do único casal fértil do
// mês anterior. Ou seja, há três casais de coelhos, dois férteis e um infértil.
//
// 5. No quinto mês há os três casais do mês anterior, já férteis, adicionados
// de dois casais recém-nascidos, resultado do acasalamento entre os dois casais
// férteis do mês anterior. Ou seja, há cinco casais de coelhos, três férteis e
// dois inférteis.
//
// O Sr. Fibonacci concluiu rapidamente que, a partir do terceiro mês,
//
// - o número de casais férteis num mês é sempre igual ao número total de casais
//   no mês anterior e
//
// - o número total de casais num mês é sempre igual à soma do número total de
//   casais existente no mês anterior com o número de casais recém-nascidos, que
//   é igual ao número de casais férteis no mês anterior e que, por isso, é
//   igual ao número total de casais existentes dois meses antes.
//
// Sendo ![F(n)](http://bit.ly/ZCdcqY) o número de casais de coelhos no mês
// ![n](http://bit.ly/Z4ELdk), então, desde que ![n>2](http://bit.ly/10vWeOB),
// ![F(n)=F(n-2)+F(n-1)](http://bit.ly/10zLPR3). Quando
// ![n=1](http://bit.ly/14HsgeM) ou ![n=2](http://bit.ly/YVICg2),
// ![F(n)=1](http://bit.ly/13V3GYG). Ou seja, esta sucessão pode ser descrita de
// forma _recursiva_, ou seja, definindo os termos da sucessão em função de
// outros termos da mesma sucessão.
//
// O que pretendemos aqui é implementar uma função que receba o mês como
// argumento e devolva o número de casais existentes nesse mês. Como não
// fornecemos apenas uma implementação, mas várias, com diferentes eficiências,
// os nomes dessas funções não poderão ser simplesmente `fibonacci()`, incluindo
// no seu nome um sufixo que identifica o tipo de implementação usado. Pode
// argumentar-se que, sendo a eficiência parte da interface de um módulo, então
// é razoável usar esses sufixos. No entanto, seria preferível, se o nosso
// objectivo não fosse o estudo dos algoritmos em si, mas a criação de
// ferramentas para utilização futura ou para disponibilização a terceiros, usar
// sufixos que fossem reveladores da eficiência da função, e não da sua
// implementação.
//
// Antes, porém, de passar às implementações, é preciso dizer que o presente
// oferecido ao Sr. Fibonacci está realmente envenenado. Com efeito, a sucessão
// de Fibonacci cresce de forma extremamente rápida. Assim, no mês 120, ou seja,
// dez anos depois da oferta do casal original, o número de casais a alimentar é
// exactamente 5&thinsp;358&thinsp;359&thinsp;254&thinsp;990&thinsp;966&thinsp;640&thinsp;871&thinsp;840.
// Este valor é demasiado grande para os `int` nas nossas máquinas habituais,
// que têm 32 _bits_, ou mesmo para os _long_, com 64 _bits_ nessas mesmas
// máquinas. Por outro lado, a precisão limitada dos tipos de virgula flutuante
// pode pôr problemas complicados ao cálculo dos termos da sucessão (já
// tínhamos dito que dos tipos de vírgula flutuante se foge como diabo da
// cruz?). O código abaixo recorre ao tipo `long`, numa tentativa de evitar que
// se atinjam muito cedo os limites dos inteiros. É uma má solução, no entanto.
// Uma boa solução passaria pela utilização de um tipo capaz de representar
// números inteiros de dimensão arbitrária (desde que haja memória para o
// guardar, bem entendido). A implementação de um tal tipo é um excelente
// exercício de algoritmos e estruturas de dados, mas não o resolveremos aqui.

// Implementação
// -------------
//
// Como se referiu, usamos `long` como tipo de devolução das funções de cálculo
// dos termos da sucessão de Fibonacci. Será que isso adianta muito, em relação
// à utilização de _int_? Fazendo algumas experiências, é fácil verificar que,
// em máquinas em que os `int` têm 32 _bits_, ou seja, em máquinas em que o
// maior valor representável num `int` é 2&thinsp;147&thinsp;483&thinsp;647, o
// maior termo da sucessão de Fibonacci representável num `int` é o termo 46, ou
// seja, ![F(46)](http://bit.ly/XgffV7), cujo valor é
// 1&thinsp;836&thinsp;311&thinsp;903. Isto é, usando `int` só conseguimos obter
// valores correctos para os primeiros 47 termos da sucessão. Usando `long`, é
// fácil verificar que, em máquinas em que os `long` têm 64 _bits_, ou seja, em
// máquinas em que o maior valor representável num `long` é
// 9&thinsp;223&thinsp;372&thinsp;036&thinsp;854&thinsp;775&thinsp;807, o maior
// termo da sucessão de Fibonacci representável num `long` é o termo 92, ou
// seja, ![F(92)](http://bit.ly/12kthcr), cujo valor é
// 7&thinsp;540&thinsp;113&thinsp;804&thinsp;746&thinsp;346&thinsp;429. Isto é,
// usando `long` só conseguimos obter valores correctos para os primeiros 93
// termos da sucessão. Melhor que os 47 se se usasse `int`, mas ainda assim um
// valor bem pequeno.
//
// O maior termo calculável usando `long`, 92, deve ser usado nas pré-condições
// das funções abaixo. Usar o valor literal nesse código é muito má ideia, pois
// torna mais difícil a compreensão do código. Afinal, haverá que perceba
// imediatamente o significado desse valor? Para resolver o problema definimos
// uma constante para guardar esse valor. Uma vez que esta constante será usada
// para dimensionar _arrays_ que pretendemos inicializar usando as usuais listas
// de inicializadores do C, não podemos usar a forma mais óbvia de definir
// constantes em C, i.e., não podemos usar
//
// ```C
// const int maximum_term_fitting_a_long = 92;
// ```
//
// tendo, pelo contrário de usar uma macro do pré-processador.
#define MAXIMUM_TERM_FITTING_A_LONG 92

// ### Inclusão de ficheiros de cabeçalho
//
// Incluímos os seguintes ficheiros de cabeçalho:
//
// - `stdio.h` &ndash; Para declaração do procedimento `printf()`.
//
// - `stdlib.h` &ndash; Para definição da _macro_ `EXIT_SUCCESS`.
//
// - `time.h` &ndash; Para definição da função `clock()` e da macro
//   `CLOCKS_PER_SEC`.
//
// - `assert.h` &ndash; Para definição da macro `assert()`.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// ### Implementação recursiva «estúpida»

// #### Documentação
// A documentação da função é feita no formato do
// [Doxygen](http://doxygen.org/), como habitualmente.
/** \brief Returns the `n`th term of the Fiboncci sequence.
 *
 * \param n The number of the term to return (first valid value is 0).
 * \return The value of the `n`th term of the Fibonacci sequence. The time taken
 * by the function grows exponentially with `n`.
 * \pre `n` ≥ 0
 * \post result = \f$F_{\mathtt{n}}\f$
 *
 * Returns the `n`th term of the Fibonacci sequence. It is assumed the sequence
 * starts at `n` = 0, with value 0, followed by value 1, at `n` = 1. That is,
 * the sequence is defined by
 * \f[
 * F_n = \left\{\begin{array}{ll}
 *     0                 & \text{if } n=0, \\
 *     1                 & \text{if } n=1\text{, and} \\
 *     F_{n-2} + F_{n-1} & \text{if } n>1.
 *   \end{array}\right.
 * \f]
 */
// #### Definição
//
// Esta implementação segue a estratégia mais comum das soluções recursivas:
// decompor o problema em problemas mais simples, resolver esses problemas mais
// simples usando exactamente a mesma estratégia, recursivamente, e compor as
// soluções dos subproblemas de modo a obter a solução do problema como um todo.
// Uma solução recursiva, como esta, precisa de possuir casos de paragem (ou
// casos especiais), para os quais a solução é imediata, não sendo necessária
// qualquer decomposição adicional. A definição recursiva da sucessão de
// Fibonacci aparenta adequar-se bem a esta estratégia:
//
// ![F(n)={0, se n = 0, 1, se n = 1, e F(n-2) + F(n-1), se n > 1}](http://bit.ly/13TPIpP)
long stupidly_recursive_fibonacci(int n)
{
	// Em primeiro lugar, verificamos as pré-condições e lidamos com as
	// violações que forem detectadas.
	assert(n >= 0);
	assert(n <= MAXIMUM_TERM_FITTING_A_LONG);

	// Depois, lidamos com os dois casos especiais da sucessão. Estes casos
	// servem também para garantir que as invocações recursivas desta função
	// acabarão sempre por terminar (em tempo finito).
	if (n == 0)
		return 0L;
	if (n == 1)
		return 1L;

	// O caso geral é simplesmente a devolução da soma dos termos anterior
	// da sucessão. Para os obter, invocamos a própria função com os dois
	// valores inteiros anteriores a `n`. O problema desta implenentação é
	// que se está a reduzir o problema de calcular
	// ![F(n)](http://bit.ly/ZCdcqY) aos subproblemas de calcular
	// ![F(n-2)](http://bit.ly/14HrTAK) e de calcular
	// ![F(n-1)](http://bit.ly/13V2Vid), _mas estes subproblemas não são
	// independentes!_
	return stupidly_recursive_fibonacci(n - 2)
		+ stupidly_recursive_fibonacci(n - 1);
}

// ### Implementação recursiva com _lookup_

// #### Documentação
// A documentação da função é feita no formato do
// [Doxygen](http://doxygen.org/), como habitualmente.
/** \brief Returns the `n`th term of the Fiboncci sequence.
 *
 * \param n The number of the term to return (first valid value is 0).
 * \return The value of the `n`th term of the Fibonacci sequence. The time taken
 * by the function grows !!!!!!!!!!!!!!!!!!!! with `n`.
 * \pre `n` ≥ 0
 * \post result = \f$F_{\mathtt{n}}\f$
 *
 * Returns the `n`th term of the Fibonacci sequence. It is assumed the sequence
 * starts at `n` = 0, with value 0, followed by value 1, at `n` = 1. That is,
 * the sequence is defined by
 * \f[
 * F_n = \left\{\begin{array}{ll}
 *     0                 & \text{if } n=0, \\
 *     1                 & \text{if } n=1\text{, and} \\
 *     F_{n-2} + F_{n-1} & \text{if } n>1.
 *   \end{array}\right.
 * \f]
 */
// #### Definição
long recursive_fibonacci(int n)
{
	// Em primeiro lugar, verificamos as pré-condições e lidamos com as
	// violações que forem detectadas.
	assert(n >= 0);
	assert(n <= MAXIMUM_TERM_FITTING_A_LONG);

	// !!!!!!!!!!!! Inicialização e static. Casos especiais.
	static long F[MAXIMUM_TERM_FITTING_A_LONG + 1] = {0, 1};
	static int number_of_calculated_terms = 2;

	// Se o termo já constar na memória de termos calculados, limitamo-nos
	// a devolvê-lo.
	if (n < number_of_calculated_terms)
		return F[n];

	// O caso geral passa por invocar recursivamente !!!!!!! ordem de cálculo é relevante?!!!!!!!
	number_of_calculated_terms++;
	return F[n] = recursive_fibonacci(n - 2) + recursive_fibonacci(n - 1);
//	number_of_calculated_terms = n + 1;
}

// ### Implementação iterativa

// #### Documentação
// A documentação da função é feita no formato do
// [Doxygen](http://doxygen.org/), como habitualmente.
/** \brief Returns the `n`th term of the Fiboncci sequence.
 *
 * \param n The number of the term to return (first valid value is 0).
 * \return The value of the `n`th term of the Fibonacci sequence. The time taken
 * by the function grows linearly with `n`.
 * \pre `n` ≥ 0
 * \post result = \f$F_{\mathtt{n}}\f$
 *
 * Returns the `n`th term of the Fibonacci sequence. It is assumed the sequence
 * starts at `n` = 0, with value 0, followed by value 1, at `n` = 1. That is,
 * the sequence is defined by
 * \f[
 * F_n = \left\{\begin{array}{ll}
 *     0                 & \text{if } n=0, \\
 *     1                 & \text{if } n=1\text{, and} \\
 *     F_{n-2} + F_{n-1} & \text{if } n>1.
 *   \end{array}\right.
 * \f]
 */
// #### Definição
long iterative_fibonacci(int n)
{
	assert(n >= 0);
	assert(n <= MAXIMUM_TERM_FITTING_A_LONG);

	if (n == 0)
		return 0L;
	if (n == 1)
		return 1L;

	long previous_term = 1L;
	long current_term = 1L;
	for(int i = 2; i != n; i++) {
		current_term += previous_term;
		previous_term = current_term - previous_term;
	}

	return current_term;
}

// ### Procedimento !!!!!!!

// #### Documentação
// !!!!!!!!
/** \brief !!!!!!!!!!!! (includes month 0)
 *
 * \param n !!!!!!!!!
 * \return !!!!!!!!!!!
 * \pre `n` ≥ 0
 * \post !!!
 *
 * !!!!!!!!!!!!!!!
 */
// #### Definição
void experiment_efficiency_of(char title[], long fibonacci(int),
			int last_term)
{
	printf("%s\n", title);
	double previous_time = 0.0;
	for (int n = 0; n != last_term + 1; n++) {
		clock_t start = clock();
		int f = fibonacci(n);
		clock_t end = clock();
		double time = (double) (end - start) / CLOCKS_PER_SEC;
		printf("f(%d) = %d in %.4fs %g\n", n, f, time,
			time / previous_time);
		previous_time = time;
	}
}

// ### Procedimento !!!!!!!
//
// !!!!!!!!
int main(void)
{
	for (int n = 0; n != 100; n++) {
//		printf("F(%d) [stupid recursive] = %ld\n", n, stupidly_recursive_fibonacci(n));
		printf("F(%d) [recursive] = %ld\n", n, recursive_fibonacci(n));
		printf("F(%d) [iterative] = %ld\n", n, iterative_fibonacci(n));
	}

	return EXIT_SUCCESS;

	experiment_efficiency_of("Stupidly recursive implementation of the fibonacci sequence:",
				stupidly_recursive_fibonacci, 35);
	experiment_efficiency_of("Three variable iterative implementation of the fibonacci sequence:",
				iterative_fibonacci, 1000);

	return EXIT_SUCCESS;
}
