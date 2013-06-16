// `print.c` &ndash; Ficheiro de implementação (modularização física)
// ==================================================================
//
// Estrutura elementar de um ficheiro de implementação
// ---------------------------------------------------
//
// Este é um dos ficheiros de implementação associados ao ficheiro de cabeçalho
// [`array_utils.h`](array_utils.html). Neste caso optou-se por manter um único
// ficheiro de cabeçalho e por dividir a implementação por vários ficheiros de
// implementação. Dessa forma:
//
// - Simplifica-se a vida de quem pretende utilizar os utilitários, pois terá de
//   incluir apenas um ficheiro de cabeçalho. Claro está que esta vantagem se
//   pode transformar numa desvantagem caso a quantidade de utilitários aumente
//   substancialmente.
//
// - Facilita-se a manutenção das implementações, pois estas ficam separadas,
//   cada uma em seu ficheiro.
//
// Note que as implementações dos vários utilitários são fornecidas na forma de
// uma _biblioteca_, ou seja, na forma de um ficheiro que arquiva os ficheiros
// objecto correspondentes a cada ficheiro de implementação. Isso significa que
// a organização das implementações apenas num grande ficheiro ou, como aqui se
// sugere, em ficheiros separados para cada utilitário, _é totalmente
// transparente_ para o programador cliente da biblioteca.
//
// Note ainda que, em Linux, a biblioteca terá o nome `libarray_utils.a`. Em C,
// o nome do ficheiro com a versão estática de uma biblioteca chamada
// <code>_biblioteca_</code> é usualmente <code>lib_biblioteca_.a</code>.
  
// ### Inclusão do cabeçalho correspondente a esta implementação
//
// Antes de qualquer outra inclusão, incluímos o ficheiro de cabeçalho
// correspondente a este ficheiro de implementação. Isso ajuda a detectar
// inconsistências entre o ficheiro de implementação e o correspondente ficheiro
// de cabeçalho.
#include "array_utils.h"

// ### Inclusão de ficheiros de cabeçalho necessários no código de implementação
//
// Estas inclusões ser feita apenas _após_ se incluir o ficheiro de cabeçalho
// corresponde ao próprio ficheiro de implementação. Neste caso temos:
//
// - `stdio.h` &ndash; Necessário para poder usar o procedimento `printf`.
//
// - `assert.h` &ndash; Necessário para se poder usar a macro `assert()` para
//   fazer asserções no código.
#include <stdio.h>
#include <assert.h>

// ### Definição de rotinas
//
// Definição de todas as rotinas correspondentes a este ficheiro. Neste caso há
// apenas uma rotina a definir: `print()`.
  
// Definição da rotina `print()`. A definição das rotinas repete (porque o C o
// impõe) o seu cabeçalho, mas segue-o de um corpo onde se define o
// funcionamento ou implementação da rotina. Note que normalmente não se incluem
// comentários de documentação (e.g., [Doxygen](http://doxygen.org)) nos
// ficheiros de implementação.
void print(int number_of_items, int items[number_of_items])
{
	// Verifica explicitamente as pré-condições desta rotina de que o
	// primeiro argumento não pode ser negativo e o segundo não pode ser um
	// ponteiro nulo.
	assert(number_of_items >= 0);
	assert(items != NULL);

	// Note a utilização de uma guarda fraca, aqui. Ou seja, usamos `i !=
	// number_of_items` em vez da guarda mais usual (e mais forte) `i <
	// number_of_items`. A vantagem de uma guarda fraca é que leva mais
	// facilmente a ciclos infinitos (ou, pelo menos, muito longos) _quando
	// o código está errado_. Isso tem a vantagem de facilitar a detecção de
	// erros. Por exemplo, o que aconteceria se a asserção acima estivesse
	// desactivada (usual no código em produção) e fosse passado um valor
	// negativo como primeiro argumento? No caso da guarda forte, o ciclo
	// terminaria e tudo _pareceria_ funcionar. No caso da guarda fraca, o
	// ciclo tornar-se-ia muito longo (mas não infinito) o que levaria à
	// mais rápida detecção do problema.
	for (int i = 0; i != number_of_items; i++)
		printf("%d\n", items[i]);
}
