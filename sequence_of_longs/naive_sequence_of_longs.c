// `sequence_of_longs.c` &ndash; Implementação das sucessões de `long`
// ===================================================================

// Implementação do módulo físico `sequence_of_longs`
// --------------------------------------------------
//
// Para uma explicação mais pormenorizada das várias partes deste ficheiro, e da
// implementação das várias rotinas,  consultar a explicação do correspondente
// ficheiro [`sequence_of_longs.c`](sequence_of_longs.c.html). Neste ficheiro
// explica-se apenas aquilo que é específico desta implementação ingénua do TAD
// sucessão de `long`.
//
// Este ficheiro de implementação contém a implementação do módulo físico
// `naive_sequence_of_longs`. A interface deste módulo encontra-se no ficheiro
// de cabeçalho ou de interface
// [`naive_sequence_of_longs.h`](naive_sequence_of_longs.h.html).
  
// ### Inclusão do cabeçalho correspondente a esta implementação
//
#include "naive_sequence_of_longs.h"

// ### Inclusão de ficheiros de cabeçalho necessários no código de implementação
//
#include <stdio.h>
#include <stdlib.h>

// ### Definição da estrutura `struct naive_sequence_of_long`
//
// Esta estrutura contém dois campos ou atributos:
//
// - `terms` &ndash; Um ponteiro para o _array_ dinâmico que contém os termos da
//   sucessão.
//
// - `length` &ndash; Inteiro guardando o comprimento actual da sucessão, i.e.,
//   o seu número de termos. Note que o comprimento da sucessão é sempre
//   igual ao comprimento do `array` que guarda os termos.
struct naive_sequence_of_longs {
	long *terms;
	int length;
};

// ### Implementação dos procedimentos que imprimem as sucessões
//
void NSEQL_print(struct naive_sequence_of_longs *sl)
{
	putchar('{');
	for (int i = 0; i != sl->length; i++) {
		if (i != 0)
			printf(", ");
		printf("%ld", sl->terms[i]);
	}
	putchar('}');
}

void NSEQL_println(struct naive_sequence_of_longs *sl)
{
	NSEQL_print(sl);
	putchar('\n');
}

// ### Implementação do construtor do TAD
//
struct naive_sequence_of_longs *NSEQL_new(void)
{
	// Reservamos primeiro espaço para uma nova `struct sequence_of_longs`
	// usando a rotina `malloc()`. Obtemos a quantidade de unidades de
	// memória a reservar usando o operador `sizeof`. Guardamos o endereço
	// dessa nova variável dinâmica no ponteiro `sl`, através do qual se
	// passará a manipular a nova sucessão de `long`. No final do construtor
	// este ponteiro será devolvido.
	struct naive_sequence_of_longs *sl =
		malloc(sizeof(struct naive_sequence_of_longs));

	// De seguida inicializamos os campos ou atributos da rotina com valores
	// apropriados para uma sucessão vazia. O comprimento de uma sucessão
	// vazia é naturalmente 0. Uma vez que não é possível ter um ponteiro
	// válido para um _array_ dinâmico com 0 itens, inicializa-se o ponteiro
	// para o primeiro item desse _array_ com o valor `NULL`.
	sl->length = 0;
	sl->terms = NULL;

	// Terminada a construção da nova sucessão, há que devolver o seu
	// endereço (ou ponteiro), guardado na variável `sl`.
	return sl;
}

// ### Implementação do _inspector_ do comprimento
//
int NSEQL_length(struct naive_sequence_of_longs *sl)
{
	return sl->length;
}

// ### Implementação do _modificador_ de adição de um novo termo à sucessão
//
void NSEQL_add(struct naive_sequence_of_longs *sl, long new_term)
{
	// Uma vez que o _array_ dinâmico tem sempre a sua capacidade esgotada,
	// adicionar um novo termo à sucessão implica sempre redimensionar esse
	// _array_. Para aumentar a capacidade, usamos a rotina `realloc()` para
	// reservar um novo _array_ dinâmico com capacidade para mais um termo
	// _e incluindo todos os termos que já constam na sucessão_. É este
	// último requisito que nos leva a usar a rotina `realloc()`, e não a
	// rotina `malloc()`. A rotina `realloc()`, se precisar de reservar nova
	// memória, i.e., se não conseguir simplesmente estender o _array_
	// existente, copiará automaticamente os termos da memória original. É
	// por isso que o primeiro argumento passado a `realloc()` é um ponteiro
	// para o _array_ original.
	sl->terms = realloc(sl->terms, (sl->length + 1) * sizeof(long));

 	// Finalmente, guardamos o novo termo `new_term` no local apropriado do
 	// _array_, que neste ponto já tem certamente (hmmmm... será?)
 	// capacidade suficiente, i.e., na posição `sl->length`. Depois,
 	// incrementamos o comprimento da sucessão.
 	sl->terms[sl->length++] = new_term;
}

// ### Implementação do _inspector_ de termo
//
long NSEQL_term(struct naive_sequence_of_longs *sl, int index)
{
	return sl->terms[index];
}


