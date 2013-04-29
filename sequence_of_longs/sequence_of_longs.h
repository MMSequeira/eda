// `sequence_of_longs.h`
// =====================

// Interface do TAD sucessão de `long`s
// ------------------------------------
//
// Este ficheiro de cabeçalho destina-se a ser utilizado pelo código cliente da
// implementação em C do TAD (Tipo Abstracto de Dados) sucessão de `long`s. Este
// ficheiro de cabeçalho faz jus ao seu nome, contendo apenas os «cabeçalhos»
// dos artefactos em causa, nada revelando acerca da sua implementação.
//
// ### Comentário de documentação do ficheiro de cabeçalho
//
// No topo do ficheiro de cabeçalho incluímos um _comentário de documentação_
// que explica o propósito e o conteúdo deste ficheiro de cabeçalho. Os
// comentários de documentação têm um formato que depende do sistema de
// documentação usado. Aqui utilizamos e recomendamos o [Doxygen](doxygen.org).
//
/**
 * \file sequence_of_longs.h
 * \brief Header file for the sequence of longs ADT (Abstract Data Type).
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

// ### Declaração da `struct` que representa as sequências de `long`s
//
//
struct sequence_of_longs;

struct sequence_of_longs *SEQL_new(void);

void SEQL_print(struct sequence_of_longs *sl);

void SEQL_println(struct sequence_of_longs *sl);

int SEQL_length(struct sequence_of_longs *sl);

void SEQL_add(struct sequence_of_longs *sl, long new_item);

long SEQL_item(struct sequence_of_longs *sl, int index);

#endif // ISLA_EDA_SEQUENCE_OF_LONGS_H_INCLUDED
