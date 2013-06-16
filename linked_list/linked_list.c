// `linked_list.c` &ndash; Cadeias simplesmente ligadas
// ====================================================
//
// Este programa ilustra de forma elementar a estrutura de dados _cadeia
// simplesmente ligada_.

// Documentação do ficheiro `linked_list.c`
// ----------------------------------------
//
// Como habitualmente, usamos o formato [Doxygen](doxygen.org) para os
// comentários de documentação.
/**
 * \file linked_list.c
 * \brief Source file containing simple singly linked list examples.
 * 
 * This source file defines the C structure `struct singly_linked_int_list_node`
 * and uses it to implement and experiment with a singly linked list.
 */

// Inclusões
// ---------
//
// As inclusões usuais de ficheiros de cabeçalho, para poder usar o procedimento
// `printf` de escrita no ecrã e para poder devolver `EXIT_SUCCESS` no final do
// programa.
#include <stdio.h>
#include <stdlib.h>

// Estrutura C `struct singly_linked_int_list_node`
// ---------------------------------------------------------------

// ### Documentação da estrutura
//
// Como habitualmente, precedemos a definição da estrutura do correspondente
// comentário de documentação do [Doxygen](doxygen.org).
/** \struct singly_linked_int_list_node
 * \brief Structure for storing a node of a singly linked list.
 *
 * Each node contains a single `int` as payload data.
 *
 * \var singly_linked_int_list_node::value
 * The `int` payload data of a node.
 *
 * \var singly_linked_int_list_node::next_node
 * The pointer to the next node in the linked list (`NULL` if
 * this is the last node in the list).
 */

// ### Definição da estrutura
//
// As _estruturas C_ são um mecanismo da linguagem C que permite definir novos
// tipos de dados. As variáveis definidas como tendo como tipo uma estrutura C
// agregam um conjunto de membros ou campos de diferentes tipos. As estruturas C
// são uma das duas categorias de tipos ditos _tipos agregados_ do C, em
// conjunto com os _arrays_. As estruturas C são muitas vezes essenciais para
// criar _estruturas de dados_, mas não devem ser confundidas com estas. As
// estruturas C são um mecanismo básico da linguagem C, enquanto as estruturas
// de dados são formas de organização dos dados que transcendem a linguagem de
// programação em particular em que estão implementadas.
//
// As _cadeias simplesmente ligadas_ são também conhecidas por _listas
// simplesmente ligadas_, mas preferimos reservar a palavra «lista» para _tipos
// abstractos de dados_ (TAD), que podem ou não recorrer a cadeias simples ou
// duplamente ligadas como forma de implementação. As cadeias simplesmente
// ligadas consistem numa sequência de _elos_ (ou _nós_), cada um deles
// guardando dados como _carga útil_ e contendo um ponteiro para o elo seguinte
// na cadeia. Estas cadeias dizem-se simplesmente ligadas por cada um dos seus
// elos ter informação apenas acerca do _elo seguinte_ na cadeia. Quando os elos
// contêm também um ponteiro para o _elo anterior_, dizem-se _cadeias duplamente
// ligadas_.
//
// No exemplo abaixo recorre-se directamente à manipulação da estrutura C
// `struct singly_linked_int_list_node`, que nos permite implementar cadeias
// simplesmente ligadas, mas é raro que as estruturas de dados sejam usadas
// directamente no código _cliente_. As estruturas de dados são usadas sobretudo
// como implementação de tipos abstractos de dados. O mesmo deveria acontecer
// neste caso, mas optámos por deixar a estrutura de dados «nua» para se
// perceber melhor como os elos se organizam e como se acede e manipula uma
// cadeia simplesmente ligada.
//
// O nome da estrutura C definida, `struct singly_linked_int_list_node` reflecte
// os seguintes factos:
//
// - Trata-se de uma estrutura C: `struct` (esta palavra-chave faz parte do nome
//   da estrutura, mas não da sua _etiqueta_, que consiste apenas no
//   identificador `singly_linked_int_list_node`).
// - Trata-se de um _elo de uma cadeia_: `list_node`.
// - Trata-se de um elo de _uma cadeia_: `list`.
// - Trata-se de um elo de uma cadeia _simplesmente ligada_: `singly_linked`.
// - Trata-se de um elo _cuja carga útil é um `ìnt`_: `int`.
//
// As variáveis pertencentes ao tipo `struct singly_linked_int_list_node` são
// usualmente elos de cadeias simplesmente ligadas. Cada uma dessas variáveis
// contém dois membros:
//
// - `value` &ndash; Um campo do tipo `int` correspondendo à _carga útil_ do elo
//   em causa.
// - `next_node` &ndash; Um _ponteiro para o elo seguinte_ da cadeia
//   simplesmente ligada a que o elo pertence.
//
// Note que o campo `next_node` é definido recorrendo à própria estrutura C em
// definição. Esta definição recursiva da estrutura C é perfeitamente legítima,
// pois o campo está a ser definido como sendo um _ponteiro_ para uma instância,
// objecto ou variável do mesmo tipo.
struct singly_linked_int_list_node {
	int value;
	struct singly_linked_int_list_node *next_node;
};

// Criação e manipulação de uma cadeia simplesmente ligada
// -------------------------------------------------------
//
// Usamos a rotina `main()` para criar e manipular uma cadeia simplesmente
// ligada.
  
// ### Documentação da rotina `main()`
//
// Como habitualmente, usamos o formato [Doxygen](doxygen.org) para os
// comentários de documentação.
/**
 * \brief Routine containing simple singly linked list example code.
 * 
 * This routine uses the C structure `struct singly_linked_int_list_node`
 * to implement and experiment with a singly linked list.
 */

// ### Definição da rotina `main()`
int main(void)
{
	// Para podermos manipular uma cadeia simplesmente ligada, precisamos de
	// uma forma de saber onde está o seu primeiro elo. Fazemo-lo através da
	// variável `first_node`, que serve justamente para apontar o primeiro
	// elo. Note que o nome desta variável é um pouco enganador: na
	// realidade esta variável não guarda o primeiro elo, mas sim _um
	// ponteiro para o primeiro elo_. Pode confirmar que se trata de um
	// ponteiro através do símbolo `*` antes do seu nome. Os nomes dos
	// restantes ponteiros usados neste programa seguem o mesmo padrão: o
	// nome refere-se àquilo que é apontado, e não ao ponteiro propriamente
	// dito.
	//
	// As cadeias ligadas só são verdadeiramente úteis se o programador
	// tiver a possibilidade de criar novos elos e de os inserir na cadeia,
	// ou de os remover e destruir, nos instantes em que isso lhe é mais
	// conveniente. Por isso, os elos das cadeias ligadas são tipicamente
	// _variáveis dinâmicas_, ou seja, variáveis construídas pelo código do
	// programador na memória dinâmica por ele reservada usando a rotina
	// `malloc()` (ou das outras rotinas do C com objectivo semelhante),
	// numa zona da memória do programa a que se chama normalmente o
	// «montão» ou _heap_, e destruídas pelo código do programador
	// libertando essa mesma memória através do procedimento `free()`.
	//
	// Esta instrução define a variável local `first_node` como um ponteiro
	// para `struct singly_linked_int_list_node` e inicializa esse ponteiro
	// com o endereço de uma zona de memória com dimensão apropriada para
	// guardar uma instância desse tipo. Essa zona de memória será
	// inicializada nas instruções seguintes como sendo o primeiro e único
	// elo da cadeia.
	struct singly_linked_int_list_node *first_node = 
		malloc(sizeof(struct singly_linked_int_list_node));
	// Para perceber o código de inicialização, bem como o que se segue,
	// precisa de se recordar que o operador `->` serve para aceder a um
	// campo de uma estrutura através de um seu ponteiro. Assim, o código
	// apresentado é equivalente a:
	//
	// ```C
	// (*first_node).value = 10;
	// (*first_node).next_node = NULL;
	// ```
	//
	// A utilização de parênteses no código acima deve-se à maior
	// precedência do operador `.` relativamente ao operador `*` (ver
	// [tabela de precedência e associatividade dos operadores do C e do
	// C++ na Wikipédia](http://bit.ly/147TVC2)).
	//
	// Através do ponteiro `first_node`, inicializamos os dois membros ou
	// campos do primeiro e único elo da cadeia. Esse elo contém como carga
	// útil o inteiro 10. A inicialização tem de incidir também sobre o
	// campo `next_node`, que de outro modo conteria um valor indefinido.
	// Mas que endereço guardar nesse campo, um ponteiro para o elo seguinte
	// na cadeia, se a cadeia ainda só tem um elo? A resposta é simples: o
	// último elo da cadeia caracteriza-se por ter o valor especial `NULL`
	// nesse campo, indicando-se com isso que não existe qualquer outro elo
	// da cadeia depois dele.
	first_node->value = 10;
	first_node->next_node = NULL;

	// Vamos agora percorrer a cadeia simplesmente ligada desde o primeiro
	// elo até o seu fim. Para isso usamos o ciclo `for` de um forma um
	// pouco diferente do usual. Na inicialização do ciclo `for`, definimos
	// uma nova variável `node`, um ponteiro para `struct
	// singly_linked_int_list_node`, que inicializamos com o endereço do
	// primeiro elo: `struct singly_linked_int_list_node *node =
	// first_node`. No progresso do ciclo `for`, fazemos o ponteiro `node`
	// avançar, atribuindo-lhe o endereço do elo seguinte em relação ao elo
	// apontado pela própria variável `node`: `node = node->next_node`. Como
	// guarda do ciclo, usamos o predicado `node != NULL`, ou seja, o ciclo
	// continua, avançando com o ponteiro `node` ao longo dos elos da
	// cadeia, até atingir o valor `NULL`, guardado no campo `next` do
	// último elo da cadeia. Em cada passo do ciclo, escrevemos no ecrã o
	// valor da carga útil do elo corrente da cadeia.
	//
	// Se lhe parece um pouco exagerado usar um ciclo `for` para percorrer
	// uma cadeia que neste ponto tem apenas um elo, tem toda a razão. É um
	// exagero. Mas pelo menos deixa claro que podemos usar um ciclo para
	// percorrer cadeias com qualquer comprimento (inclusive com comprimento
	// nulo, como veremos).
	//
	// Naturalmente, o resultado da execução deste código será:
	//
	// ```
	// After the first node insertion:
	// Node payload: 10
	// ```
	printf("After the first node insertion:\n");
	for (struct singly_linked_int_list_node *node = first_node;
		node != NULL;
		node = node->next_node)
		printf("Node payload: %d\n", node->value);
	putchar('\n');

	// Vamos agora inserir um novo elo na cadeia, no seu final. Para isso,
	// reservamos a quantidade de memória apropriada e colocamos o seu
	// endereço no membro ponteiro `next_node` do primeiro elo da cadeia,
	// apontado por `first_node`.
	first_node->next_node =
		malloc(sizeof(struct singly_linked_int_list_node));
	// Da mesma forma que anteriormente, inicializamos os membros do novo
	// elo com valores apropriados, nomeadamente com 20 na carga útil
	// `value` e com o valor especial `NULL` no ponteiro `next_node`,
	// deixando claro que não há qualquer elo após este novo elo, que é
	// agora o último da cadeia.
	first_node->next_node->value = 20;
	first_node->next_node->next_node = NULL;

	// Mostramos no ecrã o conteúdo da cadeia, tal como anteriormente. O
	// resultado da execução deste código será:
	//
	// ```
	// After the second node insertion:
	// Node payload: 10
	// Node payload: 20
	// ```
	printf("After the second node insertion:\n");
	for (struct singly_linked_int_list_node *node = first_node;
		node != NULL;
		node = node->next_node)
		printf("Node payload: %d\n", node->value);
	putchar('\n');

	// Desta vez vamos inserir um novo elo _no início_ da cadeia. Para isso,
	// começamos por construir um novo elo, guardando o seu endereço numa
	// variável local `new_node`.
	struct singly_linked_int_list_node *new_node =
		malloc(sizeof(struct singly_linked_int_list_node));
	// Inicializamos a carga útil do novo elo com o valor `int` 0 (zero). O
	// elo seguinte da cadeia, relativamente ao novo elo, é o elo que neste
	// momento é o primeiro elo da cadeia. Isto acontece porque o novo elo
	// está a ser inserido no início da cadeia, ao contrário do que fizemos
	// antes.
	new_node->value = 0;
	new_node->next_node = first_node;
	// Construído o novo elo, já com uma referência apropriada para o elo da
	// cadeia que se lhe segue, precisamos de actualizar o ponteiro
	// `first_node` de modo a apontar para o novo elo, que passará a ser o
	// primeiro elo da cadeia.
	first_node = new_node;

	// Mostramos no ecrã o conteúdo da cadeia, tal como anteriormente. O
	// resultado da execução deste código será:
	//
	// ```
	// After the third node insertion:
	// Node payload: 0
	// Node payload: 10
	// Node payload: 20
	// ```
	printf("After the third node insertion:\n");
	for (struct singly_linked_int_list_node *node = first_node;
		node != NULL;
		node = node->next_node)
		printf("Node payload: %d\n", node->value);
	putchar('\n');

	// Vamos agora remover o primeiro elo da cadeia. Para isso, poderia
	// parecer suficiente fazer avançar o ponteiro `first_node` usando a
	// atribuição `first_node = first_node->next_node`. Mas a verdade é que
	// precisamos de libertar a memória ocupada pelo primeiro elo, pelo que
	// temos de guardar o seu endereço numa variável auxiliar.
	struct singly_linked_int_list_node *node_to_free = first_node;
	first_node = first_node->next_node;
	free(node_to_free);

	// Mostramos no ecrã o conteúdo da cadeia, tal como anteriormente. O
	// resultado da execução deste código será:
	//
	// ```
	// After the first node removal:
	// Node payload: 10
	// Node payload: 20
	// ```
	printf("After the first node removal:\n");
	for (struct singly_linked_int_list_node *node = first_node;
		node != NULL;
		node = node->next_node)
		printf("Node payload: %d\n", node->value);
	putchar('\n');

	// Podemos também remover o último elo da cadeia, desde que tenhamos uma
	// forma simples de aceder ao seu penúltimo elo. Neste momento o
	// penúltimo elo é também o primeiro elo da cadeia, pelo que o acesso é
	// fácil.
	struct singly_linked_int_list_node *next_to_last_node = first_node;
	// A remoção propriamente dita tem dois passos. O primeiro passo é
	// libertar a memória reservada para o último elo.
	free(next_to_last_node->next_node);
	// O segundo passo é actualizar o campo `next_node` do que agora é o
	// último elo, atribuindo-lhe o valor especial `NULL`. Isso marca-o como
	// último elo da cadeia.
	next_to_last_node->next_node = NULL;

	// Mostramos no ecrã o conteúdo da cadeia, tal como anteriormente. O
	// resultado da execução deste código será:
	//
	// ```
	// After the second node removal:
	// Node payload: 10
	// ```
	printf("After the second node removal:\n");
	for (struct singly_linked_int_list_node *node = first_node;
		node != NULL;
		node = node->next_node)
		printf("Node payload: %d\n", node->value);
	putchar('\n');

	// Neste momento a cadeia tem apenas um elo. Removê-lo é fácil, bastando
	// libertar a sua memória e colocar o valor especial `NULL` no ponteiro
	// `first_node`, deixando assim claro que a cadeia está agora vazia.
	free(first_node);
	first_node = NULL;

	// Mostramos no ecrã o conteúdo da cadeia, tal como anteriormente. O
	// ciclo não sofre qualquer alteração, funcionando por isso
	// correctamente, _mesmo para cadeias vazias_. O resultado da execução
	// deste código será:
	//
	// ```
	// After the third node removal:
	// ```
	printf("After the third node removal:\n");
	for (struct singly_linked_int_list_node *node = first_node;
		node != NULL;
		node = node->next_node)
		printf("Node payload: %d\n", node->value);

	// Terminamos assinalando sucesso.
	return EXIT_SUCCESS;
}
