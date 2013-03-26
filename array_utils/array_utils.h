// `array_utils.h` &ndash; Estrutura elementar de ficheiros de cabeçalho
// =====================================================================

// Na linguagem C, o mecanismo de modularização de um programa em pacotes
// físicos, ou seja, o mecanismo de divisão em diferentes ficheiros, é muito
// primitivo. Implica a manutenção de dois tipos de ficheiros em paralelo: (a)
// os ficheiros com as implementações dos módulos físicos (ficheiros em código
// fonte, com a extensão `.c`, antes de compilados, ficheiros objecto, com a
// extensão `.o`/`.obj`, depois de compilados em linguagem máquina, ou
// bibliotecas, com a extensões `.a`/`.lib` ou `.so`/`.dll`, depois de
// arquivados para fusão estática ou dinâmica)  e (b) os ficheiros com as
// interfaces desses módulos físicos, com a extensão `.h`, e aos quais se dá o
// nome de _ficheiros de cabeçalho_.

// Comentário de documentação do ficheiro de cabeçalho
// ---------------------------------------------------
//
// No topo do ficheiro de cabeçalho incluímos um _comentário de documentação_
// que explica o propósito e o conteúdo deste ficheiro de cabeçalho. Os
// comentários de documentação têm um formato que depende do sistema de
// documentação usado. Aqui utilizamos e recomendamos o [Doxygen](doxygen.org).
//
// Notas:
//
// 1. Os comentários que estão escritos em português, tal como este mesmo, nunca
//    surgiriam em código real: trata-se de informação útil apenas para efeitos
//    de ensino no contexto da unidade curricular de EDA, do ISLA Campus Lisboa
//    | Laureate International Universities. Como tal, surgem apenas na coluna
//    esquerda da documentação gerada pelo
//    [Docco](http://jashkenas.github.com/docco/). Ver
//    [array_utils.h](array_utils.html).
//
// 2. Os comentários de documentação não surgem nas listagens de código fonte
//    criadas pelo Doxygen. Ou seja, as linhas imediatamente abaixo destas no
//    código fonte serão omitidas na [listagem deste
//    ficheiro](http://mmsequeira.github.com/eda/html/array__utils_8h_source.html).
//
// 3. A informação contida no comentário de documentação é usada para compor a
//    documentação sobre este ficheiro. Ver
//    [array_utils.h](http://mmsequeira.github.com/eda/html/array__utils_8h.html). 
//
/**
 * \file array_utils.h
 * \brief Header file for the array utilities.
 * 
 * This header file declares all the array utilities available for use
 * throughout the EDA code.
 */

// Protecção contra inclusões múltiplas
// ------------------------------------
//
// Os ficheiros de cabeçalho são usados através de um mecanismo também ele muito
// primitivo: a directiva de inclusão (`#include`) do pré-processador. Este
// mecanismo leva a que seja frequente a ocorrência de múltiplas inclusões do
// mesmo ficheiro de cabeçalho. Isso é problemático se levar à definição
// múltipla de artefactos que podem ser definidos apenas num local. Para evitar
// esse problema, é usual recorrer-se à utilização de directivas de pré-
// processamento de formas semipadronizadas. É o que fazemos aqui.
//
// Todo o código do ficheiro de cabeçalho fica envolto numa instrução
// condicional do pré-processador. Ou seja, esse código só é considerado pelo
// compilador se a macro `ISLA_EDA_ARRAY_UTILS_H_INCLUDED` não estiver definida.
// Se isso acontecer, a macro em causa será definida, de modo a que futuras
// inclusões (duplicadas) não levem a considerar o código do ficheiro de
// cabeçalho uma segunda vez. O nome escolhido para a macro é convencional e
// destina-se e evitar colisões com outras macros relativas a outros ficheiros
// de cabeçalho ou com identificadores usados por _clientes_ do ficheiro de
// cabeçalho, i.e., por programadores que pretendam usar as ferramentas por ele
// declaradas, sem estarem necessariamente envolvidos na sua implementação. A
// convenção aqui usada é a seguinte:
//
// - Seguir a convenção usual de usar apenas maiúsculas como nome de macros,
//   separando as palavras pelo caracteres sublinhado (_underscore_), ou seja,
//   `_`.
//
// - Não alterar o nome usado depois de este ser exposto a uma utilização real.
//   De outra forma, corre-se o risco (mesmo que menor) de regressões, i.e., de
//   que código funcional deixe de funcionar depois de uma alteração.
//
// - Usar como prefixo um identificador da organização que produziu a versão
//   original do ficheiro de cabeçalho. Neste caso usamos `ISLA_EDA`.
//
// - De seguida, colocar o nome do ficheiro de cabeçalho, neste caso
//   `ARRAY_UTILS_H`, incluindo possivelmente um prefixo adicional com o nome da
//   biblioteca a que pertence.
//
// - Terminar com `_INCLUDED`.
//
#ifndef ISLA_EDA_ARRAY_UTILS_H_INCLUDED
#define ISLA_EDA_ARRAY_UTILS_H_INCLUDED

// Declarações
// -----------
//
// Finalmente, o objectivo deste ficheiro de cabeçalho é declarar (e, em alguns
// casos, definir) as ferramentas disponibilizadas pelo módulo físico (ou pelos
// módulos físicos) que lhe correspondem.

// ### Comentário de documentação de rotina
//
// A declaração é precedida de um _comentário de documentação_ que indica
// claramente qual o contrato desta rotina. Mais uma vez, usamos aqui o
// [Doxygen](doxygen.org).
/** \brief Print a given array's items in `stdout`, one item per line.
 *
 * \param number_of_items The number of items of the array `items` to print.
 * \param items The array (or rather, a pointer to its first item) whose
 * items will be printed.
 * \return Nothing (it is a procedure).
 * \pre `number_of_items` ≥ 0
 * \pre `items` ≠ null
 * \pre `items` points to an array with at least `number_of_items` items
 *
 * This procedure prints `number_of_items` items from the array `items`. It
 * prints each item of the array in a separate line.
 */
// ### Declaração propriamente dita
//
// Procedimento de impressão dos itens de um _array_. A declaração não inclui
// corpo, que seria parte da implementação do módulo. Inclui apenas o
// _cabeçalho_ do procedimento, pois é o que é necessário para verificar a
// correcção sintáctica das utilizações desta rotina. A definição do
// procedimento encontra-se no _ficheiro de implementação_
// [`print.c`](print.html).
void print(int number_of_items, int items[number_of_items]);

// Final da instrução condicional do pré-processador.
#endif // ISLA_EDA_ARRAY_UTILS_H_INCLUDED
