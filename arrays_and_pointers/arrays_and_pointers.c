// `arrays_and_pointers.c` &ndash; Ponteiros e _arrays_
// ====================================================
/**
 * \file arrays_and_pointers.c
 * \brief Illustrates the relation between arrays and pointers in C.
 * 
 * This C file illustrating the relation between arrays and pointers in the C
 * language. The code is presented tongue-in-cheek, since if makes use C rules
 * regarding arrays, pointers, and indexing to produce silly and obscure code. 
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// Regras do C sobre _arrays_ e ponteiros
	// --------------------------------------
	//
	// A linguagem C tem uma forma perfeitamente consistente, embora
	// idiossincrática, de lidar com _arrays_ e ponteiros. Algumas das
	// regras usadas pelo C são:
	//
	// 1. Sempre que o nome de um _array_ surge numa expressão (com algumas
	// excepções, tal como quando operando do operador `sizeof`), é
	// convertido    num ponteiro para o seu primeiro item. Assim, se `m`
	// for um _array_, então    `m` e `&m[0]` são expressões equivalentes.
	//
	// 2. A utilização do operador de indexação, e.g., na expressão `m[i]`,
	// é    equivalente à «desreferenciação» do ponteiro obtido da soma
	// entre o    objecto indexado e o índice usado. Assim, `m[i]` tem
	// exactamente o mesmo    significado que `*(m + 1)`, ou seja, quando
	// `m` for um _array_, `m[i]` é exactamente o mesmo que `*(&m[0] +
	// 1)`.
	//
	// O código abaixo evidencia estas regras pelo absurdo. Por favor, não
	// tire partido das regras enunciadas para escrever código
	// incompreensível!
	  
	// O nome `m` é o nome de um _array_ com três números inteiros: 1, 2 e
	// 3.
	int m[] = {1, 2, 3};

	for (int i = 0; i != 3; i++)
		// Como chegar a este código? Simples:
		//
		// * `m[i]` é o mesmo que `*(m + i)`, pela segunda regra acima.
		// * `*(m + i)` é o mesmo que `*(i + m)`, pela comutatividade da
		//   adição.
		// * `*(i + m)` é o mesmo que `i[m]`, de novo pela segunda regra
		//   acima.
		printf("%d\n", i[m]);

	// Este caso é absolutamente idêntico, se se tiver em conta que uma
	// cadeia de caracteres literal em C é equivalente à definição de um
	// _array_ de `char` (e não `const char`, como seria expectável) com um
	// nome aleatório (que não colida com qualquer nome existente no
	// programa) e com o mesmo número de caracteres da cadeia literal, e à
	// utilização desse nome no código no local onde se encontra a cadeia de
	// caracteres literal. Assim, o código é equivalente ao seguinte:
	//
	// ```C
	// char a_random_name[] = "Hello";
	// for (int i = 0; i != sizeof(a_random_name) - 1; i++)
	//         putchar(i[a_random_name]);
	// ```
	//
	// Pelas regras indicadas mais acima, este código é equivalente ao
	// seguinte:
	//
	// ```C
	// char a_random_name[] = "Hello";
	// for (int i = 0; i != sizeof(a_random_name) - 1; i++)
	//         putchar(a_random_name[i]]);
	// ```
	//
	// Atenção! Não confunda inicialização com atribuição! Na instrução
	// 
	// ```C
	// char a_random_name[] = "Hello";
	// ```
	//
	// não há qualquer atribuição. O que ocorre, isso sim, é uma
	// inicilização. Neste contexto, `"Hello"` não é visto como uma cadeia
	// de caracteres literal, mas sim como um inicializador.
	for (int i = 0; i != sizeof("Hello") - 1; i++)
		putchar(i["Hello"]);

	// Terminamos assinalando que o programa teve sucesso.
	return EXIT_SUCCESS;
}
