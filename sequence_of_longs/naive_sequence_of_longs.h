// `naive_sequence_of_longs.h` &ndash; Interface das sucessões de `long`
// =====================================================================

// Interface do módulo físico `naive_sequence_of_longs`
// ----------------------------------------------
//
// Para uma explicação mais pormenorizada das várias partes deste ficheiro,
// consultar a explicação do correspondente ficheiro
// [`sequence_of_longs.h`](sequence_of_longs.h.html).
//
// Este ficheiro de cabeçalho destina-se a ser utilizado pelo código cliente do
// módulo físico `naive_sequence_of_longs`. A implementação deste módulo
// encontra-se no ficheiro de implementação
// [`naive_sequence_of_longs.c`](naive_sequence_of_longs.c.html). Este módulo
// físico contém o TAD (Tipo Abstracto de Dados) sucessão (ingénua) de `long`,
// com o mesmo nome que o módulo físico, i.e., `naive_sequence_of_longs`.
//
// A utilização da palavra «naive» («ingénua») neste módulo físico e no TAD que
// lhe corresponde não passa de uma brincadeira. Na realidade, um termo mais
// adequado seria «slow» («lenta»). Trata-se de um TAD com exactamente a mesma
// interface e funcionalidade que o TAD `sequence_of_long`, mas com uma
// diferença importante a nível da eficiência com que os novos termos da
// sucessão são adicionados, que é neste caso muito menor. De facto, a
// implementação usada garante que a memória usada para guardar os termos é tão
// pequena quanto possível, mas fá-lo à custa de um tempo de inserção de novos
// termos que cresce linearmente com o comprimento da sucessão.
  
// ### Comentário de documentação do ficheiro de cabeçalho
//
/**
 * \file naive_sequence_of_longs.h
 * \brief Header file for the `naive_sequence_of_longs` module, containing the
 * ADT (Abstract Data Type) with the same name: `naive_sequence_of_longs`.
 *
 * This header file declares the basic structure used to store the sequences
 * of longs and all the routines used to manipulate these sequences.
 */

// ### Protecção contra inclusões múltiplas
//
#ifndef ISLA_EDA_NAIVE_SEQUENCE_OF_LONGS_H_INCLUDED
#define ISLA_EDA_NAIVE_SEQUENCE_OF_LONGS_H_INCLUDED

// ### Comentário de documentação da `struct` `sequence_of_long`
//
// Este comentário de documentação serve para gerar documentação estruturada
// sobre esta estrutura, como aliás acontece nos restantes casos em que este
// tipo de comentário é usado.
//
/** \brief C structure used to represent the sequence of `long`s and to
 * store its terms.
 *
 * This TAD guarantees tight memory allocation. That is, the memory used is as
 * small as strictly necessary to store the terms of the sequence. This,
 * however, is achieved at the cost of inefficient addition of new terms. The
 * time necessary to add new terms grows linearly with the length of the
 * sequence.
 */
// ### Declaração da `struct` que representa as sucessões de `long`
//
struct naive_sequence_of_longs;

// ### Construtor do TAD
//
/** \brief Returns a pointer to a newly created and initialized
 * `naive_sequence_of_longs`.
 *
 * \return A pointer to a newly (heap) allocated and initialized
 * `struct naive_sequence_of_longs`. 
 * \post The returned pointer refers to a new `struct naive_sequence_of_longs`
 * representing an empty (i.e., length 0) sequence of `long`s.
 *
 * This function is a constructor of the sequence of `long`s ADT.
 */
struct naive_sequence_of_longs *NSEQL_new(void);

// ### Operações do TAD

/** \brief Prints the sequence of longs in the format `{term_1, ... term_n}`.
 *
 * \param sl A pointer to the sequence of `long`s to print.
 * \pre `sl` ≠ null
 */
void NSEQL_print(struct naive_sequence_of_longs *sl);

/** \brief Prints the sequence of longs in the format `{term_1, ... term_n}` and
 * ends the line with `\n`.
 *
 * \param sl A pointer to the sequence of `long`s to print.
 * \pre `sl` ≠ null
 */
void NSEQL_println(struct naive_sequence_of_longs *sl);

/** \brief Returns the number of terms so far in a given sequence of `long`s.
 *
 * \param sl A pointer to the sequence of `long`s whose length will be returned.
 * \return The number of terms in the sequence so far.
 * \pre `sl` ≠ null
 */
int NSEQL_length(struct naive_sequence_of_longs *sl);

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
 * The time required to add the new term varies linearly with the length of the
 * sequence.
 */
void NSEQL_add(struct naive_sequence_of_longs *sl, long new_term);

/** \brief Returns the term of the given sequence at the given position or
 * index. 
 *
 * \param sl A pointer to the sequence of `long`s whose length will be returned.
 * \param index The index or position of the term of the sequence to return.
 * \return The term of the sequence given in the position or index given.
 * \pre `sl` ≠ null
 * \pre 0 ≤ `index` < `NSEQL_length(sl)`
 */
long NSEQL_term(struct naive_sequence_of_longs *sl, int index);

// ### Fim do ficheiro
//
// Final da instrução condicional do pré-processador.
#endif // ISLA_EDA_NAIVE_SEQUENCE_OF_LONGS_H_INCLUDED