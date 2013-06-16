// `sequence_of_longs.c` &ndash; Implementação das sucessões de `long`
// ===================================================================

// Implementação do módulo físico `sequence_of_longs`
// --------------------------------------------------
//
// Este ficheiro de implementação contém a implementação do módulo físico
// `sequence_of_longs`. A interface deste módulo encontra-se no ficheiro de
// cabeçalho ou de interface [`sequence_of_longs.h`](sequence_of_longs.h.html).
// Este módulo físico contém o TAD (Tipo Abstracto de Dados) sucessão de `long`,
// com o mesmo nome que o módulo físico, i.e., `sequence_of_longs`. Este
// ficheiro de implementação faz jus ao seu nome, contendo as implementações
// correspondentes aos «cabeçalhos», i.e., às interfaces, que se encontram no
// correspondente ficheiro de cabeçalho.
//
// Note-se que este ficheiro não possui comentários de documentação (começados
// por `/**`). Tratando-se de um ficheiro de implementação, nada contém que seja
// relevante na documentação do módulo físico, já que esta está relacionada
// apenas com a sua interface.
  
// ### Inclusão do cabeçalho correspondente a esta implementação
//
// Antes de qualquer outra inclusão, incluímos o ficheiro de cabeçalho
// correspondente a este ficheiro de implementação. Isso ajuda a detectar
// inconsistências entre o ficheiro de implementação e o correspondente ficheiro
// de cabeçalho.
#include "sequence_of_longs.h"

// ### Inclusão de ficheiros de cabeçalho necessários no código de implementação
//
// Estas inclusões ser feita apenas _após_ se incluir o ficheiro de cabeçalho
// corresponde ao próprio ficheiro de implementação. Neste caso temos:
//
// - `stdio.h` &ndash; Necessário para poder usar os procedimentos `printf()` e
//   `putchar()`.
//
// - `stdlib.h` &ndash; Necessário para se poder usar a macro `NULL` (que será
//   usada no futuro) e as rotinas  `malloc()`, `free()` e `realloc()`.
#include <stdio.h>
#include <stdlib.h>

// ### Definição da estrutura `struct sequence_of_long`
//
// Esta estrutura contém três campos ou atributos:
//
// - `terms` &ndash; Um ponteiro para o _array_ dinâmico que contém os termos da
//   sucessão.
//
// - `length` &ndash; Inteiro guardando o comprimento actual da sucessão, i.e.,
//   o seu número de termos. Note que o comprimento da sucessão é sempre
//   inferior ou igual ao comprimento do `array` que guarda os termos, a que
//   chamamos «capacidade».
//
// - `capacity` &ndash; Inteiro guardando o comprimento actual do `array`
//   dinâmico que guarda os `length` termos actualmente na sucessão.
struct sequence_of_longs {
	long *terms;
	int length;
	int capacity;
};

// ### Implementação dos procedimentos que imprimem as sucessões
//
// Note-se que todas as rotinas de manipulação das sucessões, com excepção
// naturalmente do construtor, recebem um ponteiro para a sucessão em causa como
// primeiro argumento. Convencionou-se chamar `sl` ao correspondente parâmetro
// em todas as definições de rotinas abaixo, com a excepção referida.
void SEQL_print(struct sequence_of_longs *sl)
{
	// O procedimento `putchar()` imprime no ecrã o caractere que recebe
	// como argumento. Neste caso trata-se da chaveta inicial da
	// representação textual da sucessão.
	putchar('{');

	// Depois de impressa a chaveta inicial, imprimimos cada um dos termos
	// da sucessão usando um ciclo `for`. Note que o ciclo imprime apenas os
	// termos da sucessão, e não todos os itens do _array_ dinâmico que os
	// armazena. Daí que a sua guarda se refira a `sl->length`, e não a
	// `sl->capacity`.
	for (int i = 0; i != sl->length; i++) {
		// Os termos são separados uns dos outros por `,␣` (usamos o
		// caractere `␣` para representar o espaço). Assim, podemos
		// preceder cada termo do separador _com excepção do primeiro_.
		if (i != 0)
			printf(", ");

		// Imprimimos cada termo usando a especificação de conversão
		// `%ld`, e não simplesmente `%d`, pois os termos da sucessão
		// são `long`.
		printf("%ld", sl->terms[i]);
	}

	// Terminamos imprimindo a chaveta de fecho.
	putchar('}');
}

void SEQL_println(struct sequence_of_longs *sl)
{
	// Neste caso a implementação é fácil. Começa-se por invocar o
	// procedimento acima:
	SEQL_print(sl);

	// Depois imprime-se o caractere `\n`, para finalizar a linha:
	putchar('\n');
}

// ### Implementação do construtor do TAD
//
struct sequence_of_longs *SEQL_new(void)
{
	// Reservamos primeiro espaço para uma nova `struct sequence_of_longs`
	// usando a rotina `malloc()`. Obtemos a quantidade de unidades de
	// memória a reservar usando o operador `sizeof`. Guardamos o endereço
	// dessa nova variável dinâmica no ponteiro `sl`, através do qual se
	// passará a manipular a nova sucessão de `long`. No final do construtor
	// este ponteiro será devolvido.
	struct sequence_of_longs *sl = malloc(sizeof(struct sequence_of_longs));

	// De seguida inicializamos os campos ou atributos da rotina com valores
	// apropriados para uma sucessão vazia. O comprimento de uma sucessão
	// vazia é naturalmente 0. A capacidade do _array_ dinâmico que guarda
	// os termos também poderia ser inicialmente 0. No entanto, como se verá
	// mais abaixo, a estratégia usada é a de duplicar a capacidade sempre
	// que ela está esgotada e se pretende adicionar um termo à sucessão.
	// Ora, uma capacidade de 0 estaria esgotada logo na primeira adição de
	// um termo e, pior, o dobro de 0 é... 0! É mais sensato, por isso,
	// começar com um capacidade maior que zero. Começar com 1 é uma
	// possibilidade, embora qualquer outro valor positivo fosse igualmente
	// eficaz. Quanto maior for a capacidade inicial, maior a eficiência das
	// adições, mas pior a eficiência na utilização da memória. Daí que a
	// escolha de uma capacidade inicial unitária não seja totalmente
	// desprovida de sentido.
	//
	// Ah! E não se esqueça que o compilador traduz `sl->length` por
	// `(*sl).length`. Ou seja, o significado de `sl->length` é «o campo
	// `length` da estrutura apontada pelo ponteiro `sl`».
	sl->length = 0;
	sl->capacity = 1;

	// Inicializados os campos que guardam o comprimento da sucessão e a
	// capacidade do _array_ dinâmico que guarda os termos da sucessão, há
	// que reservar espaço de memória para este _array_ e guardar o endereço
	// do seu primeiro item no campo `terms`. É o que se faz aqui,
	// recorrendo à rotina `malloc()`. Note-se que se reserva espaço
	// suficiente para `sl->capacity` termos.
	sl->terms = malloc(sl->capacity * sizeof(long));

	// Terminada a construção da nova sucessão, há que devolver o seu
	// endereço (ou ponteiro), guardado na variável `sl`. Será através dele
	// que o código cliente fará uso da sucessão, passando-o como primeiro
	// argumento às rotinas fornecidas por este módulo físico.
	return sl;
}

// ### Implementação do _inspector_ do comprimento
//
// Dá-se o nome de inspector a uma função que permite obter uma propriedade de
// uma instância de um TAD sem alterar essa instância. (A palavra «instância»
// não tem nada de especial. Uma «instância» é um exemplar ou caso particular de
// um tipo. Por exemplo, o valor `5` é uma instância do tipo `int`, em C.)
//
int SEQL_length(struct sequence_of_longs *sl)
{
	return sl->length;
}

// ### Implementação do _modificador_ de adição de um novo termo à sucessão
//
// Dá-se o nome de modificador a um procedimento que altera uma instância de um
// TAD. Neste caso o modificador é o procedimento `SEQL_add()`, que altera a
// sucessão cujo ponteiro é `sl` adicionando-lhe um novo termo `new_term`.
//
void SEQL_add(struct sequence_of_longs *sl, long new_term)
{
	// Antes de adicionar o termo há que verificar se o _array_ dinâmico
	// onde será guardado tem capacidade suficiente para ele. Se o
	// comprimento actual da sucessão for igual à capacidade desse _array_,
	// então a capacidade está esgotada, sendo necessário aumentá-la.
	if (sl->length == sl->capacity)
		// Para aumentar a capacidade, duplicamos o valor do campo
		// `sl->capacity` e usamos a rotina `realloc()` para reservar um
		// novo _array_ dinâmico com essa nova capacidade _e incluindo
		// todos os termos que já constam na sucessão_. É este último
		// requisito que nos leva a usar a rotina `realloc()`, e não a
		// rotina `malloc()`. A rotina `realloc()`, se precisar de
		// reservar nova memória, i.e., se não conseguir simplesmente
		// estender o _array_ existente, copiará automaticamente os
		// termos da memória original. É por isso que o primeiro
		// argumento passado a `realloc()` é um ponteiro para o _array_
		// original.
		sl->terms = realloc(sl->terms,
				    (sl->capacity *= 2) * sizeof(long));

	// Estas linhas poderiam ser substituídas pelo código abaixo. À parte a
	// possibilidade de estender o _array_ original, de que a rotina
	// `realloc()` pode tirar partido, o resultado seria exactamente o
	// mesmo. Preferimos, naturalmente, a versão mais curta... Quanto à
	// duplicação da capacidade numa instrução à parte, é certamente
	// preferível, mas é tão comum (idiomático) encontrar o código
	// condensado numa única instrução, que optámos pela versão mais
	// críptica.
	//
	// ```C
	// if (sl->length == sl->capacity) {
	//	   sl->capacity *= 2;
	//	   long *new_array = malloc(sl->capacity * sizeof(long));
	//	   for (int i = 0; i != sl->length; i++)
	//		   new_array[i] = sl->terms[i];
	//	   free(sl->terms);
	//	   sl->terms = new_array;
	// }
	// ```
  
 	// Finalmente, guardamos o novo termo `new_term` no local apropriado do
 	// _array_, que neste ponto já tem certamente (hmmmm... será?)
 	// capacidade suficiente, i.e., na posição `sl->length`. Depois,
 	// incrementamos o comprimento da sucessão. Mais uma vez, a condensação
 	// de duas alterações numa única instrução é uma má prática, mas tão
 	// generalizada na programação em C que já se tornou idiomática. A
 	// alternativa, mais clara, seria usar:
 	//
 	// ```C
	// sl->terms[sl->length] = new_term;
	// sl->length++;
 	// ```
	sl->terms[sl->length++] = new_term;
}

// ### Implementação do _inspector_ de termo
//
// Este inspector permite obter o termo da sucessão na posição dada por _index_.
//
long SEQL_term(struct sequence_of_longs *sl, int index)
{
	// Note a utilização da indexação do item `index` do _array_ dinâmico
	// `sl->terms`, ao qual se acede usando o operador `->` sobre o ponteiro
	// `sl` para a estrutura que representa a sucessão.
	return sl->terms[index];
}

