// `arrays_basics.c` &ndash; Noções sobre _arrays_
// ===============================================
/**
 * \file arrays_basics.c
 * \brief An introduction, in code, to the basics about arrays. 
 */

// O básico sobre os _arrays_
// --------------------------
//
// ### O que são os _arrays_
//
// Os _arrays_ são uma das formas de agregar dados em C. Nos _arrays_ os dados,
// a que chamamos «itens», são todos do mesmo tipo. Estes dados estão
// organizados numa sequência com um comprimento fixo. Por exemplo,
//
// ```C
// int array[4];
// ```
// define um novo _array_ com exactamente quatro inteiros.
//
// ### Inicialização de _arrays_
//
// #### Inicialização por omissão
//
// Tal como acontece no caso de variáveis dos tipos básicos da linguagem, por
// omissão o C _não_ inicializa os itens de um _array_ (desde que seja um
// _array_ automático, pois se for estático todos os itens são inicializados com
// um valor nulo). Ou seja, estes começam a sua vida com valores que, do ponto
// de vista do programador, são puro lixo, mesmo que provavelmente estes valores
// consistam simplesmente numa interpretação do padrão de _bits_ que se encontra
// na memória alocada para esses itens ou variáveis.
//
// #### Inicialização explícita
//
// Os _arrays_ podem ser inicializados explicitamente através de uma lista
// de inicializadores:
//
// ```C
// int array[4] = {0, 1, 2};
// ```
//
// Neste caso omitimos o valor inicial do quarto item do _array_. Quando isto
// acontece, o compilador do C encarrega-se de gerar código máquina que
// inicializa os itens em falta com valores nulos. Podemos, por isso, usar um
// truque simpático para inicializar todos os itens dos _arrays_ do C com o
// valor zero (no entanto, a norma que especifica o C11 não é clara quanto à
// validade de usar uma lista de inicialização vazia...):
//
// ```C
// int array[4] = {};
// ```
//
// Quando se fornece uma lista de inicialização, é possível omitir a
// dimensão dos _arrays_. Nesse caso, o _array_ terá como dimensão o número
// de valores colocado entre chavetas. Por exemplo, o código
//
// ```C
// int array[] = {0, 1, 2};
// ```
//
// define um _array_ com exactamente três itens.
  
// Inclusão de ficheiros de cabeçalho
// ----------------------------------
//
// Inclusão de ficheiros de cabeçalho:
//
// - `stdio.h` &ndash; Para declaração do procedimento `printf()`.
//
// - `stdlib.h` &ndash; Para definição da _macro_ `EXIT_SUCCESS`.
//
// - `assert.h` &ndash; Para definição da macro `assert()`.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Incluímos também o ficheiro de cabeçalho `array_utils.h`, pois contém a declaração
// do procedimento `void print(int number_of_items, int
// items[number_of_items])`, usado mais abaixo. A inclusão está a ser feita
// encerrando o nome do ficheiro entre aspas, e não entre parênteses agudos.
// Isso faz com que o compilador procure o ficheiro não apenas nos locais padrão
// habituais (e.g., `/usr/include`) mas também no próprio projecto em que nos
// encontramos. Neste caso o ficheiro está no projecto Code::Blocks
// `array_utils`, cujo propósito é a criação de uma biblioteca de utilitários
// para lidar com _arrays_. Note que não basta que este ficheiro de cabeçalho,
// contendo o _protótipo_, esteja disponível para inclusão durante o processo de
// construção (mais precisamente durante o pré-processamento): é necessário que
// esteja também disponível uma biblioteca ou um ficheiro objecto com o
// resultado da compilação do ou dos ficheiros de implementação correspondentes.
// Essa biblioteca ou ficheiro objecto será _fundido_ com os restantes ficheiros
// objecto e bibliotecas durante o passo da _fusão_ do código.
//
// É de notar que a ordem de inclusão dos ficheiros de cabeçalho é relevante e
// que devemos seguir algumas boas práticas:
//
// - Se a inclusão se realiza dentro do ficheiro de implementação de um _módulo
//   físico_, então a primeira inclusão deve ser a do correspondente ficheiro de
//   cabeçalho.
//
// - As inclusões de ficheiros de cabeçalho da biblioteca padrão (ou de outras
//   bibliotecas com um estatuto de quase-padrão ou de alguma forma oficiais)
//   devem ser feitas antes da inclusão dos ficheiros de cabeçalho específicas
//   do próprio projecto.
//
// Grosso modo, devemos incluir primeiro o próprio `.h`, depois os que se
// incluem com `<>` e finalmente os que se incluem com `""`.
#include "array_utils.h"

// Definição de uma função
// -----------------------
//
// Definimos uma função que devolve a média dos itens da matriz passada como
// argumento. Uma definição de uma rotina consiste num _cabeçalho_, onde se
// caracteriza a interface da rotina, e num _corpo_, onde se coloca a
// _implementação_ da rotina. Neste caso temos uma _definição_, e não uma
// simples _declaração_, pois incluímos o corpo da função. Todas as definições
// são também declarações, mas nem todas as declarações são definições. Uma
// declaração simples, sem indicação da implementação, inclui apenas o cabeçalho
// da rotina seguido de um ponto e vírgula. O ficheiro
// [`array_utils.h`](array_utils.html) contém apenas a declaração da função.
//
// ### Documentação e cabeçalho da função
//
// O _cabeçalho_ de uma rotina declara a sua existência e especifica a sua forma
// de utilização, mas não especifica totalmente a _interface_ da função. A
// interface completa de uma rotina inclui informação mais pormenorizada acerca
// dos objectivos da rotina, acerca do significado dos parâmetros, etc., mas,
// sobretudo, estabelece um contrato claro entre o _programador produtor_ da
// rotina, i.e., o ou os programadores que a implementam e mantêm, e o
// _programador consumidor ou cliente_ da rotina, i.e., o ou os programadores
// que a usam no seu código. O C não suporta directamente a especificação da
// interface completa da rotina. Por isso, essa especificação é feita recorrendo
// a um _comentário de documentação_.
  
// #### Documentação
//
// O cabeçalho é precedido de um _comentário de documentação_ que indica
// claramente qual o contrato desta função. Usamos aqui o formato de
// documentação [Doxygen](doxygen.org).
//
// O comentário de documentação inclui:
//
// - Descrição breve da função.
// - Descrição mais longa da função (no final).
// - Descrição de cada parâmetro.
// - Descrição do valor devolvido.
// - Indicação das pré-condições (do contrato).
// - Indicação das pós-condições (do contrato).
/** \brief Returns the average of the items of a given array.
 *
 * \param number_of_items The number of items of the array `items` to consider.
 * \param items The array (or rather, a pointer to its first item) whose
 * items will be averaged.
 * \return The average of the first `number_of_items` items of array `items`.
 * \pre `number_of_items` ≥ 0
 * \pre `items` ≠ null
 * \pre `items` points to an array with at least `number_of_items` items
 * \post result = \f$\frac{\sum_{i=0}^{\mathtt{number\_of\_items}-1}
 *                \text{items}[i]}{\mathtt{number\_of\_items}}\f$
 *                (unless `number_of_items` is zero, in which case result = NaN)
 *
 * This function calculates and returns the average of the first
 * `number_of_items` items of array `items`.
 */
//
// #### Cabeçalho
//
// Este cabeçalho inclui a seguinte informação:
//
// - Nome da função &ndash; O nome da função deve ser tão explícito e claro
//   quanto possível. Pense numa possível utilização da função para chegar a um
//   bom nome. Por exemplo, suponha-se que existe um _array_ chamado
//   `student_grades` com a lista das notas de um dado aluno e se pretende saber
//   se a sua média ultrapassa os 15 valores. O código a escrever seria o que se
//   segue, que é legível quase como se se tratasse de inglês:
//
// ```C
// if (average_of(student_grades) > 15.0)
//         ...
// ```
//
// - Tipo do valor devolvido &ndash; No caso de se tratar de um procedimento, o
//   mais natural será usar `void`, e não devolver nada (embora em C seja
//   bastante usual devolver um valor que permita lidar com potenciais erros).
//   No caso de se tratar de uma função, será o tipo do valor a devolver quando
//   esta retornar. Neste caso pretende-se devolver a média de um conjunto de
//   itens inteiros. Como a média de números inteiros só esporadicamente será
//   também um número inteiro, optou-se por um tipo que abarca valores
//   racionais.
//
// - Tipo e nome de cada dos parâmetros que serão inicializados com o valor do
//   argumento respectivo sempre que a rotina for invocada. Neste caso
//   particular declaram-se dois parâmetros. O primeiro é um inteiro que será
//   inicializado com o número dos itens do _array_ sobre os quais se deve
//   devolver a média. O segundo é o _array_ que contém os itens cuja média será
//   devolvida.
double average_of(int number_of_items, int items[number_of_items])

// #### E no entanto...
//
// E no entanto, o número de itens no segundo parâmetro é ignorado pelo C. Isso
// mesmo: ignorado. Sempre que o C encontra uma declaração de um parâmetro como
// um _array_, ignora a dimensão do _array_. Ou seja, o cabeçalho usado é
// equivalente ao seguinte:
//
// ```C
// double average_of(int number_of_items, int items[])
// ```
//
// Sendo assim, como pode o compilador saber qual a dimensão do _array_? Bem,
// não pode! É que as transformações não ficam por aqui. O compilador, na
// realidade, não se limita a ignorar a dimensão do _array_. Na realidade altera
// a declaração de qualquer parâmetro que esteja uma _array_ num ponteiro para o
// tipo dos itens desse _array_. Ou seja, na realidade a declaração de um
// parâmetro como _array_ é _pura cosmética_. O que não é necessariamente mau,
// pois essa «cosmética» pode deixar mais clara a intenção do programador do que
// uma versão mais fiel à realidade. Será que prefere mesmo a versão fiel? Veja
// o resultado:
//
// ```C
// double average_of(int number_of_items, int* items)
// ```
//
// Nesta última versão não é de todo claro, excepto pelo facto de o nome do
// parâmetro estar no plural, de que se trata de um _array_ de itens.
  
// ### Corpo da função
//
// Tal como o cabeçalho de uma rotina é parte da especificação da sua interface,
// especificando parcialmente o seu «como se usa», o corpo de uma rotina é a sua
// implementação, definindo o seu «como funciona». O corpo de uma rotina
// estrutura-se usualmente como se segue:
//
// 1. Verificação de pré-condições. Verificam-se duas pré-condições, nesta
// função.
//
// 2. Resolução de casos especiais, por ordem decrescente de especificidade. Não
// se aplica nesta função.
//
// 3. Resolução do caso geral.
//
// 4. Verificação de pós-condições. No nosso caso não é prático verificar a pós-
// condição, infelizmente.
//
// 4. Retorno da rotina, com possível devolução de um valor. Neste caso retorna-
// se devolvendo a média pretendida.

{
	// Há três formas muito diferentes de lidar com as violações das pré-
	// condições.
	//
	// A primeira forma, usada aqui, passa por fazer asserções acerca das
	// pré- condições. As asserções são proposições que se afirma serem
	// verdadeiras acerca do estado do programa. Se as asserções forem
	// realizadas recorrendo à _macro_ `assert()`, então o programa abortará
	// no caso de alguma das proposições testada não ser verdadeira. Por
	// exemplo, na função em definição afirma-se que o primeiro argumento
	// não pode ser negativo e que o segundo não pode ser um ponteiro nulo.
	// Embora estas afirmações não esgotem as pré- condições da função, são
	// as que é possível ou prático fazer. Tal como no caso das pós-
	// condições, é um bom exercício tentar cobrir as pré-condições, tanto
	// quanto possível ou prático, com asserções. Que acontece quando uma
	// das asserções desta função, a primeira, por exemplo, falha? Para além
	// de o programa abortar, é mostrada uma mensagem de erro apropriada:
	//
	// <pre>
	// Assertion failed: (number_of_items >= 0), function average_of,
	// file /Users/mmsequeira/Projects/eda/arrays_basics/arrays_basics.c,
	// line 311.
	// </pre>
	//
	// Esta primeira forma de lidar com violações de pré-condições é também
	// a única aceitável no caso da violação de pós-condições, uma vez o
	// erro é detectado pelo mesmo troço de código que o causou, não havendo
	// por isso qualquer possibilidade de recuperação: trata-se sempre do
	// programador produtor da rotina em causa.
	//
	// A segunda forma de lidar com violações de pré-condições reconhece que
	// a responsabilidade por estas violações não é do programador produtor
	// da rotina, mas sim do programador cliente, sendo por isso boa ideia
	// dar a esse programador uma possibilidade de recuperar dos seus
	// próprios erros. Para o permitir, a rotina, ao detectar a violação,
	// retorna imediatamente, devolvendo um valor especial que indica ter
	// ocorrido um erro. No caso de um procedimento, que sem esta
	// preocupação não devolveria nada, usando `void` como tipo de
	// devolução, é fácil e convencional lidar com erros: o tipo de
	// devolução passa a `int` e a devolução que um qualquer valor não nulo
	// significa que ocorreu um erro. O valor exacto devolvido pode ser
	// usado como um código permitindo identificar o tipo de erro ocorrido.
	// A devolução de 0 tem o significado oposto: significa que o
	// procedimento foi executado com sucesso. No caso de uma função, esta
	// solução só pode ser usada se o conjunto imagem da função (o conjunto
	// dos valores que a função pode devolver em caso de sucesso) não
	// esgotar o seu contra-domínio (dado pelo tipo de devolução). Ou seja,
	// pode ser usado se a função _não for sobrejectiva_ e, por isso, se
	// podem usar valores que não pertençam à imagem da função como códigos
	// de erro. Por exemplo, uma função de calcule e devolva um comprimento
	// de uma sequência tem o tipo `int` com contradomínio mas como imagem
	// tem apenas os inteiros não negativos, pelo que qualquer valor
	// negativo pode ser usado como código de erro. Esta segunda forma de
	// lidar com os erros não é possível no caso desta função, pois qualquer
	// valor do tipo `double` é média de um número indefinido de possíveis
	// _arrays_.
	//
	// A terceira forma de lidar com erros passa por usar uma variável
	// global para registar um código do erro ocorrido. Embora usada, esta
	// forma de assinalar erros é muito perigosa, tal como qualquer programa
	// que recorra a variáveis globais o é. Para mais informação estude o
	// ficheiro de cabeçalho da biblioteca padrão
	// [`errno.h`](http://en.wikipedia.org/wiki/Errno.h).
	assert(number_of_items >= 0);
	assert(items != NULL);

	// A variável `sum` é um _acumulador_ que guarda, em cada passo do
	// ciclo, a soma dos primeiros `i` itens do _array_ `items` (note como,
	// mesmo sabendo que `items` é um ponteiro para o primeiro item de um
	// _array_, e não um _array_ propriamente dito, continuamos a chamar-lhe
	// _array_). Uma vez que a acumulação a realizar é uma soma, o
	// acumulador é inicializado com o elemento neutro da soma: 0 (zero).
	double sum = 0.0;

	// O ciclo percorre os primeiros `number_of_items` itens do _array_
	// `items`, actualizando as variáveis `sum` e `i` de forma a que `sum`
	// se mantenha sempre como a soma dos primeiros `i` items de `items` e
	// de forma a que `i` progrida um a um, desde o valor inicial até
	// atingir o valor `número_de_itens`.
	for (int i = 0; i != number_of_items; i++)
		sum += items[i];

	// A função retorna devolvendo a média pretendida, que é dada pelo
	// quociente entre a soma calculada e o número de items somados.
	return sum / number_of_items;

// Final da definição da função `average_of()`.
}

// O procedimento `main()`
// -----------------------
//
// Este procedimento é o ponto de entrada dos programas em C. É a primeira
// rotina a ser invocada nos programas em C. Neste caso particular queremos
// ignorar possíveis argumentos da linha de comandos, pelo que declaramos o
// procedimento colocando apenas `void` na lista de parâmetros.
//
// Note que, ao contrário do que acontece noutras linguagens, `int main()` não
// significa que o procedimento não receba qualquer argumento: significa que
// recebe argumentos não especificados. Trata-se de um resquício do passado da
// linguagem C que há que evitar a todo o custo. Para indicar que uma rotina não
// recebe qualquer argumento deve usar-se sempre `void` na lista de parâmetros.
//
// Apesar de se tratar de um procedimento, não se usa `void` como tipo de
// devolução. Isso deve-se ao facto de os possível erros ocorridos durante a
// execução do programa serem codificados através do valor inteiro devolvido.
// Esta prática é comum e foi apresentada mais atrás. O valor a devolver é
// usualmente 0, mas em rigor depende do sistema operativo (estamos a devolver
// um valor ao retornar da execução da primeira rotina do programa, pelo que o
// valor devolvido é usado pela entidade que executou o programa, possivelmente
// o sistema operativo). Assim, é comum usar as macros `EXIT_SUCCESS` para
// assinalar sucesso e `EXIT_FAILURE` para assinalar um erro.
//
// O programa, no nosso caso, tem um objectivo simples: escrever no ecrã uma
// sequência de idades de alunos dada e, em seguida, indicar qual a média de
// idades desses alunos.
int main(void)
{
	// Definição do _array_ `student_ages` com inicialização explícita. Note
	// que não indicámos explicitamente o tamanho do _array_, pelo que o
	// compilador o calculará contando o número de valores da lista de
	// inicializadores. Neste caso, por isso, o número de itens é 4.
	int student_ages[] = {23, 24, 25, 26};
	// O C não fornece nenhuma forma directa de obter o número de itens de
	// um _array_. No entanto, quando acesso ao _array_ propriamente dito, e
	// não a um ponteiro para o seu primeiro item, podemos usar um truque
	// interessante para obter esse número: usar o operador `sizeof` para
	// obter o espaço total em octetos ocupado pelo _array_ em memória e
	// dividi-lo pelo espaço ocupado em memória por cada um dos seus itens.
	// É isso que é feito neste local. O resultado é guardado numa
	// _constante_, ou seja, numa «variável» que, devido ao qualificador
	// `const`, o compilador não permitirá que seja alterada. Note que é boa
	// ideia declarar explicitamente como constantes todos os _objectos_ que
	// não se pretenda alterar depois de inicializados.
	const int number_of_students =
		sizeof(student_ages) / sizeof(int);

	// Invocação do procedimento `print()`, definido noutro local, passando
	// o número de alunos como primeiro argumento e o _array_ com as suas
	// idades como segundo argumento. Mais uma vez, é importante perceber
	// que, na realidade, e ao contrário do que a frase anterior sugere, o
	// que é passado como primeiro argumento _não é_ o _array_
	// `student_ages`, mas sim _um ponteiro para o seu primeiro item_.
	print(number_of_students, student_ages);

	// Impressão da média no ecrã. A média é obtida como resultado da
	// invocação da função `average_of()` passando-lhe os parâmetros
	// apropriados.
	printf("The average age is %g.\n",
		average_of(number_of_students, student_ages));

	// Retorno do procedimento devolvendo ao sistema operativo o valor
	// apropriado para assinalar que a execução teve sucesso.
	return EXIT_SUCCESS;
}

// É possível pedir ao utilizador o número de idades cuja média pretende e
// pedir-lhe também que insira cada uma das idades. O código abaixo implementa
// essa ideia, embora de forma demasiado simplista, pois não verifica os
// valores introduzidos pelo utilizador. Sob esse ponto de vista, o programa
// está errado, note-se.
//
// ```C
// int main(void)
// {
//         printf("How many students? ");
//         int number_of_students;
//         scanf("%d", &number_of_students);
//
//         int student_ages[number_of_students];
//         for (int i = 0; i != number_of_students; i++) {
//                 printf("Please enter age no. %d: ", i);
//                 scanf("%d", &student_ages[i]);
//         }
// 
//         print(number_of_students, student_ages);
//
//         printf("The average age is %g.\n",
//                 average_of(number_of_students, student_ages));
//         return EXIT_SUCCESS;
// }
// ```