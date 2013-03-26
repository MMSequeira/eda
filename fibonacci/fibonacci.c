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
// Ofereceram ao o Sr. Fibonacci um casal de coelhos, recém-nascidos, de um
// espécie curiosa: tornam-se férteis ao fim de um mês de vida, concebem logo
// que possível, têm uma gestação de exactamente um mês, cada ninhada consiste
// sempre num casalinho de coelhos. Nunca morrem. O Sr. Fibonacci preocupou-se:
// teria comida que chegue para os coelhos? Pôs-se calcular a evolução do número
// de casais de coelhos ao longo do tempo:
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
// Sendo ![F(n)](http://latex.codecogs.com/gif.latex?F%28n%29) o número de casais de
// coelhos no mês ![n](http://latex.codecogs.com/gif.latex?n), então, desde que
// ![n>2](http://latex.codecogs.com/gif.latex?n%3E2),
// ![F(n)=F(n-2)+F(n-1)](http://latex.codecogs.com/gif.latex?F%28n%29%3DF%28n-2%29%2BF%28n-1%29). Quando
// ![n=1](http://latex.codecogs.com/gif.latex?n%3D1) ou
// ![n=2](http://latex.codecogs.com/gif.latex?n%3D2),
// ![F(n)=1](http://latex.codecogs.com/gif.latex?F%28n%29%3D1). Ou seja, esta sucessão
// pode ser descrita de forma _recursiva_, ou seja, definindo os termos da
// sucessão em função de outros termos da mesma sucessão.
//
// O que se pretende aqui é implementar uma função `fibonacci()` que receba o
// mês como argumento e devolva o número de casais existentes nesses mês.

// Implementação
// -------------
//
// ### Inclusão de ficheiros de cabeçalho
//
// Inclusão de ficheiros de cabeçalho:
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
long stupidly_recursive_fibonacci(int n)
{
	assert(n >= 0);

	if (n == 0)
		return 0L;
	if (n == 1L)
		return 1L;
	return stupidly_recursive_fibonacci(n - 2)
		+ stupidly_recursive_fibonacci(n - 1);
}

// ### Implementação iterativa
  
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
long iterative_fibonacci(int n)
{
	assert(n >= 0);

	if (n == 0)
		return 0L;
	if (n == 1L)
		return 1L;

	long f_i_1 = 1, f_i_2 = 0;
	for(int i = 1; i != n + 1; i++) {
		long f_i = f_i_2 + f_i_1;
		f_i_2 = f_i_1;
		f_i_1 = f_i;
	}

	return f_i_1;
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
	experiment_efficiency_of("Stupidly recursive implementation of the fibonacci sequence:",
				stupidly_recursive_fibonacci, 35);
	experiment_efficiency_of("Three variable iterative implementation of the fibonacci sequence:",
				iterative_fibonacci, 1000);

	return EXIT_SUCCESS;
}
