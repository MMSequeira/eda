// Regras do C sobre _arrays_ e ponteiros
// ====================================
//
// A linguagem C, tem uma forma perfeitamente consistente, embora
// idiossincrática, de lidar com _arrays_ e ponteiros. Algumas das regras usadas
// pelo C são:
//
// 1. Sempre que o nome de um _array_ surge numa expressão (com algumas
//    excepções, tal como quando operando do operador `sizeof`), é convertido
//    num ponteiro para o seu primeiro item. Assim, se `m` for um _array_, então
//    `m` e `&m[0]` são expressões equivalentes.
// 2. A utilização do operador de indexação, e.g., na expressão `m[i]`, é
//    equivalente à «desreferenciação» do ponteiro obtido da soma entre o
//    objecto indexado e o índice usado. Assim, `m[i]` tem exactamente o mesmo
//    significado que `*(m + 1)`, ou seja, quando `m` for um _array_, `m[i]` é
//    exactamente o mesmo que `*(&m[0] + 1)`.
//
// O programa abaixo evidencia estas regras pelo absurdo. Por favor, não tire
// partido das regras enunciadas para escrever código incompreensível!

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// O nome `m` é o nome de uma matriz com três números inteiros: 1, 2 e
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
	// nome aleatório, com o mesmo número de caracteres da cadeia literal, e
	// à utilização desse nome no código.
	for (int i = 0; i != sizeof("Hello") - 1; i++)
		putchar(i["Hello"]);

	return EXIT_SUCCESS;
}
