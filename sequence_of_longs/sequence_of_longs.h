// `sequence_of_longs.h` &ndash; Interface das sucessões de `long`
// ===============================================================

// Interface do módulo físico `sequence_of_longs`
// ----------------------------------------------
//
// Este ficheiro de cabeçalho destina-se a ser utilizado pelo código cliente do
// módulo físico `sequence_of_longs`. Os ficheiros de cabeçalho ou ficheiros de
// interface contêm apenas a interface de um dado módulo físico. A implementação
// deste módulo encontra-se no ficheiro de implementação
// [`sequence_of_longs.c`](sequence_of_longs.c.html). Este módulo físico contém
// o TAD (Tipo Abstracto de Dados) sucessão de `long`, com o mesmo nome que o
// módulo físico, i.e., `sequence_of_longs`. Este ficheiro de cabeçalho faz jus
// ao seu nome, contendo apenas os «cabeçalhos», i.e., as interfaces, dos
// artefactos em causa, nada revelando acerca da sua implementação.
  
// ### Comentário de documentação do ficheiro de cabeçalho
//
// No topo do ficheiro de cabeçalho incluímos um _comentário de documentação_
// que explica o propósito e o conteúdo deste ficheiro de cabeçalho. Os
// comentários de documentação têm um formato que depende do sistema de
// documentação usado. Aqui utilizamos e recomendamos o [Doxygen](doxygen.org).
//
/**
 * \file sequence_of_longs.h
 * \brief Header file for the `sequence_of_longs` module, containing the ADT
 * (Abstract Data Type) with the same name: `sequence_of_longs`.
 *
 * This header file declares the basic structure used to store the sequences
 * of longs and all the routines used to manipulate these sequences.
 */

// ### Protecção contra inclusões múltiplas
//
// Todo o código do ficheiro de cabeçalho fica envolto numa instrução
// condicional do pré-processador. Ou seja, esse código só é considerado pelo
// compilador se a macro `ISLA_EDA_SEQUENCE_OF_LONGS_H_INCLUDED` não estiver
// definida. Se isso acontecer, a macro em causa será definida, de modo a que
// futuras inclusões (duplicadas) não levem a considerar o código do ficheiro de
// cabeçalho uma segunda vez.
//
#ifndef ISLA_EDA_SEQUENCE_OF_LONGS_H_INCLUDED
#define ISLA_EDA_SEQUENCE_OF_LONGS_H_INCLUDED

// ### Comentário de documentação da `struct` `sequence_of_long`
//
// Este comentário de documentação serve para gerar documentação estruturada
// sobre esta estrutura, como aliás acontece nos restantes casos em que este
// tipo de comentário é usado.
//
/** \struct sequence_of_longs
 * \brief C structure used to represent the sequence of `long`s and to
 * store its terms.
 *
 * This TAD guarantees constant time additions of new terms, but at the cost of
 * allocating more memory than strictly necessary. The memory allocated may
 * approach the double of the minimum strictly necessary memory.
 */
// ### Declaração da `struct` que representa as sucessões de `long`
//
// Note que não é uma definição da estrutura, mas sim uma sua mera declaração.
// Sem acesso à definição da estrutura, o código cliente deste módulo físico não
// pode declarar directamente variáveis do tipo `struct sequence_of_longs`
// (e.g., na pilha), nem tão pouco pode reservar directamente variáveis
// dinâmicas desse tipo (no monte), usando `malloc()` e recorrendo ao operador
// `sizeof`: sem acesso à definição da estrutura, o compilador não pode
// adivinhar quanto espaço deve reservar para estas variáveis, seja na pilha
// (_stack_), seja no monte (_heap_).
//
// A definição da estrutura neste local, em vez da declaração existente,
// eliminaria estas restrições. No entanto, levaria a uma pior separação entre
// interface e implementação, pois alterações na forma de representação do TAD
// levariam quase inevitavelmente a alterações na definição da estrutura e, por
// isso, a alterações neste ficheiro de interface e, consequentemente, à
// necessidade de recompilar todo o código cliente deste módulo físico, ou seja,
// todo o código que inclui este ficheiro de interface.
//
struct sequence_of_longs;

// ### Construtor do TAD
//
// Tendo acesso apenas à declaração da estrutura `struct sequence_of_longs`, o
// código cliente não pode criar directamente variáveis desse tipo, nem na
// pilha, nem no monte. O máximo que pode fazer é declarar e manipular
// indirectamente variáveis dinâmicas desse tipo que sejam criadas
// indirectamente através de rotinas associadas ao TAD em causa. Esta função tem
// justamente como objectivo permitir ao código cliente obter um ponteiro para
// uma nova variável dinâmica do tipo `struct sequence_of_longs` devidamente
// inicializada e pronta a ser usada por meio das restantes rotinas fornecidas
// neste módulo e declaradas neste ficheiro.
//
// Note-se que o nome desta função, como de resto o nome de todas as restantes
// rotinas da interface do TAD, tem o prefixo `SEQL_`. A utilização destes
// prefixos é convencional e tem como objectivo reduzir a probabilidade de
// ocorrência de conflitos entre nomes de rotinas diferentes módulos físicos,
// possivelmente em diferentes bibliotecas.
//
/** \brief Returns a pointer to a newly created and initialized
 * `sequence_of_longs`.
 *
 * \return A pointer to a newly (heap) allocated and initialized
 * `struct sequence_of_longs`. 
 * \post The returned pointer refers to a new `struct sequence_of_longs`
 * representing an empty (i.e., length 0) sequence of `long`s.
 *
 * This function is a constructor of the sequence of `long`s ADT.
 */
struct sequence_of_longs *SEQL_new(void);

// ### Operações do TAD
//
// Seguem-se as declarações de todas as operações do TAD, representadas aqui por
// rotinas, i.e., funções e procedimentos, do C. Note-se que todas estas rotinas
// recebem um _ponteiro_ para uma `struct sequence_of_long` como argumento. Isto
// adequa-se à ideia de que o código cliente pode apenas recorrer a variáveis
// dinâmicas para usar este TAD. A colocação desse ponteiro como primeiro
// argumento das rotinas é uma convenção do C (ver, por exemplo, `fprintf()`)
// que tem a vantagem de permitir um mapeamento mental mais fácil para o que
// ocorreria se o TAD fosse implementado usando uma linguagem orientada por
// objectos, em que esse ponteiro seria passado implicitamente e estaria
// acessível através de um nome convencional, como `this` ou `self`.

/** \brief Prints the sequence of longs in the format `{term_1, ... term_n}`.
 *
 * \param sl A pointer to the sequence of `long`s to print.
 * \pre `sl` ≠ null
 */
void SEQL_print(struct sequence_of_longs *sl);

/** \brief Prints the sequence of longs in the format `{term_1, ... term_n}` and
 * ends the line with `\n`.
 *
 * \param sl A pointer to the sequence of `long`s to print.
 * \pre `sl` ≠ null
 */
void SEQL_println(struct sequence_of_longs *sl);

/** \brief Returns the number of terms so far in a given sequence of `long`s.
 *
 * \param sl A pointer to the sequence of `long`s whose length will be returned.
 * \return The number of terms in the sequence so far.
 * \pre `sl` ≠ null
 */
int SEQL_length(struct sequence_of_longs *sl);

/** \brief Adds a given value as a further term of the given sequence of
 * `long`s.
 *
 * \param sl A pointer to the sequence of `long`s to which the new term will be
 * added.
 * \param new_term The new term to add to the sequence.
 * \post The sequence contains the same terms it contained before, in the same
 * order, plus the new term in its last position.
 * \pre `sl` ≠ null
 *
 * The time required to add the new term depends on the non-observable state of
 * the sequence. If this time is amortized over the series of additions prior to
 * addition being performed, then this time is constant with regards to the
 * length of the sequence.
 */
void SEQL_add(struct sequence_of_longs *sl, long new_term);

/** \brief Returns the term of the given sequence at the given position or
 * index. 
 *
 * \param sl A pointer to the sequence of `long`s whose length will be returned.
 * \param index The index or position of the term of the sequence to return.
 * \return The term of the sequence given in the position or index given.
 * \pre `sl` ≠ null
 * \pre 0 ≤ `index` < `SEQL_length(sl)`
 */
long SEQL_term(struct sequence_of_longs *sl, int index);

// ### Fim do ficheiro
//
// Final da instrução condicional do pré-processador.
#endif // ISLA_EDA_SEQUENCE_OF_LONGS_H_INCLUDED

// ### Considerações finais
//
// O que falta aqui? Bem, falta pelo menos um procedimento para libertação
// disciplinada da memória associada a uma sucessão de `long`s. Isto porque a
// utilização de `free()` pelo código cliente levará inevitavelmente a uma fuga
// de memória, nomeadamente a memória em que os termos da sucessão são
// armazenados.
//
// Falta também equipar a implementação de todas as rotinas com a correspondente
// verificação das pré-condições e com critérios para lidarem com as respectivas
// violações.
//
// Finalmente, falta lidar de forma airosa com possível falhas durante a reserva
// de memória.