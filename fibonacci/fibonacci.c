// `fibonacci.c`
// =============
/**
 * \file fibonacci.c
 * \brief Illustrates possible implementations of the calculation of terms of
 * the Fibonacci sequence.
 *
 * Iterative and recursive implementations of the calculation of terms of
 * the Fibonacci sequence. These implementations are used to illustrate
 * iteration vs. recursion, and also to show how a naïve implementation of
 * recursion may lead to serious problems.
 */

// Coelhos, recursão e iteração
// ----------------------------
//
// Ofereceram ao Sr. Fibonacci um casal de coelhos, recém-nascidos, de um
// espécie curiosa: tornam-se férteis ao fim de um mês de vida, concebem logo
// que possível, têm uma gestação de exactamente um mês, cada ninhada consiste
// sempre num casalinho de coelhos. Nunca morrem. O Sr. Fibonacci preocupou-se:
// teria comida que chegue para os coelhos? Pôs-se a calcular a evolução do
// número de casais de coelhos ao longo do tempo:
//
// 0. No mês zero o Sr. Fibonacci vivia feliz, sem qualquer coelho. Mal
// calculava o seu destino...
//
// 1. No primeiro mês há um casal de coelhos inférteis.
//
// 2. No segundo mês há um casal de coelhos, já férteis e, claro está, com a
// coelha no início da gestação de mais um casalinho.
//
// 3. No terceiro mês há o casal de coelhos original, fértil, e já no início da
// gestação de mais um casalinho de coelhos. E há, claro está, um casal recém-
// nascido e, por isso, infértil. Ou seja, há dois casais de coelhos, um fértil
// e outro infértil.
//
// 4. No quarto mês há os dois casais do mês anterior, já férteis, adicionados
// de um casal recém-nascido, resultado do acasalamento do único casal fértil do
// mês anterior. Ou seja, há três casais de coelhos, dois férteis e um infértil.
//
// 5. No quinto mês há os três casais do mês anterior, já férteis, adicionados
// de dois casais recém-nascidos, resultado do acasalamento entre os dois casais
// férteis do mês anterior. Ou seja, há cinco casais de coelhos, três férteis e
// dois inférteis.
//
// O Sr. Fibonacci concluiu rapidamente que, a partir do terceiro mês,
//
// - o número de casais férteis num mês é sempre igual ao número total de casais
//   no mês anterior e
//
// - o número total de casais num mês é sempre igual à soma do número total de
//   casais existente no mês anterior com o número de casais recém-nascidos, que
//   é igual ao número de casais férteis no mês anterior e que, por isso, é
//   igual ao número total de casais existentes dois meses antes.
//
// Sendo ![F(n)](http://bit.ly/ZCdcqY) o número de casais de coelhos no mês
// ![n](http://bit.ly/Z4ELdk), então, desde que ![n>2](http://bit.ly/10vWeOB),
// ![F(n)=F(n-2)+F(n-1)](http://bit.ly/10zLPR3). Quando
// ![n=1](http://bit.ly/14HsgeM) ou ![n=2](http://bit.ly/YVICg2),
// ![F(n)=1](http://bit.ly/13V3GYG). Ou seja, esta sucessão pode ser descrita de
// forma _recursiva_, ou seja, definindo os termos da sucessão em função de
// outros termos da mesma sucessão.
//
// O que pretendemos aqui é implementar uma função que receba o mês como
// argumento e devolva o número de casais existentes nesse mês. Como não
// fornecemos apenas uma implementação, mas várias, com diferentes eficiências,
// os nomes dessas funções não poderão ser simplesmente `fibonacci()`, incluindo
// no seu nome um sufixo que identifica o tipo de implementação usado. Pode
// argumentar-se que, sendo a eficiência parte da interface de um módulo, então
// é razoável usar esses sufixos. No entanto, seria preferível, se o nosso
// objectivo não fosse o estudo dos algoritmos em si, mas a criação de
// ferramentas para utilização futura ou para disponibilização a terceiros, usar
// sufixos que fossem reveladores da eficiência da função, e não da sua
// implementação.
//
// Antes, porém, de passar às implementações, é preciso dizer que o presente
// oferecido ao Sr. Fibonacci está realmente envenenado. Com efeito, a sucessão
// de Fibonacci cresce de forma extremamente rápida. Assim, no mês 120, ou seja,
// dez anos depois da oferta do casal original, o número de casais a alimentar é
// exactamente 5&thinsp;358&thinsp;359&thinsp;254&thinsp;990&thinsp;966&thinsp;640&thinsp;871&thinsp;840.
// Este valor é demasiado grande para os `int` nas nossas máquinas habituais,
// que têm 32 _bits_, ou mesmo para os _long_, com 64 _bits_ nessas mesmas
// máquinas. Por outro lado, a precisão limitada dos tipos de virgula flutuante
// pode pôr problemas complicados ao cálculo dos termos da sucessão (já
// tínhamos dito que dos tipos de vírgula flutuante se foge como diabo da
// cruz?). O código abaixo recorre ao tipo `long`, numa tentativa de evitar que
// se atinjam muito cedo os limites dos inteiros. É uma má solução, no entanto.
// Uma boa solução passaria pela utilização de um tipo capaz de representar
// números inteiros de dimensão arbitrária (desde que haja memória para o
// guardar, bem entendido). A implementação de um tal tipo é um excelente
// exercício de algoritmos e estruturas de dados, mas não o resolveremos aqui.

// Implementação
// -------------
//
// Como se referiu, usamos `long` como tipo de devolução das funções de cálculo
// dos termos da sucessão de Fibonacci. Será que isso adianta muito, em relação
// à utilização de _int_? Fazendo algumas experiências, é fácil verificar que,
// em máquinas em que os `int` têm 32 _bits_, ou seja, em máquinas em que o
// maior valor representável num `int` é 2&thinsp;147&thinsp;483&thinsp;647, o
// maior termo da sucessão de Fibonacci representável num `int` é o termo 46, ou
// seja, ![F(46)](http://bit.ly/XgffV7), cujo valor é
// 1&thinsp;836&thinsp;311&thinsp;903. Isto é, usando `int` só conseguimos obter
// valores correctos para os primeiros 47 termos da sucessão. Usando `long`, é
// fácil verificar que, em máquinas em que os `long` têm 64 _bits_, ou seja, em
// máquinas em que o maior valor representável num `long` é
// 9&thinsp;223&thinsp;372&thinsp;036&thinsp;854&thinsp;775&thinsp;807, o maior
// termo da sucessão de Fibonacci representável num `long` é o termo 92, ou
// seja, ![F(92)](http://bit.ly/12kthcr), cujo valor é
// 7&thinsp;540&thinsp;113&thinsp;804&thinsp;746&thinsp;346&thinsp;429. Isto é,
// usando `long` só conseguimos obter valores correctos para os primeiros 93
// termos da sucessão. Melhor que os 47 se se usasse `int`, mas ainda assim um
// valor bem pequeno.
//
// O maior termo calculável usando `long`, 92, deve ser usado nas pré-condições
// das funções abaixo. Usar o valor literal nesse código é muito má ideia, pois
// torna mais difícil a compreensão do código. Afinal, haverá que perceba
// imediatamente o significado desse valor? Para resolver o problema definimos
// uma constante para guardar esse valor. Uma vez que esta constante será usada
// para dimensionar _arrays_ que pretendemos inicializar usando as usuais listas
// de inicializadores do C, não podemos usar a forma mais óbvia de definir
// constantes em C, i.e., não podemos usar
//
// ```C
// const int maximum_term_fitting_a_long = 92;
// ```
//
// tendo, pelo contrário de usar uma macro do pré-processador.
#define MAXIMUM_TERM_FITTING_A_LONG 92

// ### Inclusão de ficheiros de cabeçalho
//
// Incluímos os seguintes ficheiros de cabeçalho:
//
// - `stdio.h` &ndash; Para declaração do procedimento `printf()`.
//
// - `stdlib.h` &ndash; Para definição da _macro_ `EXIT_SUCCESS`.
//
// - `time.h` &ndash; Para definição da função `clock()` e da macro
//   `CLOCKS_PER_SEC`.
//
// - `assert.h` &ndash; Para definição da macro `assert()`.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// ### Inclusão de ficheiros de cabeçalho próprios
//
// Incluímos apenas um ficheiro de cabeçalho «não oficial»:
//
// - `sequence_of_longs.h` &ndash; Para declaração do TAD sucessão de `long`
// usada para guardar em memória dos termos da sucessão já calculados.
#include "sequence_of_longs.h"

// ### Implementação recursiva «estúpida»

// #### Documentação
// A documentação da função é feita no formato do
// [Doxygen](http://doxygen.org/), como habitualmente.
/** \brief Returns the `n`th term of the Fiboncci sequence.
 *
 * \param n The number of the term to return (first valid value is 0).
 * \return The value of the `n`th term of the Fibonacci sequence. The time taken
 * by the function grows exponentially with `n`.
 * \pre `n` ≥ 0
 * \post result = \f$F_{\mathtt{n}}\f$
 *
 * Returns the `n`th term of the Fibonacci sequence. It is assumed the sequence
 * starts at `n` = 0, with value 0, followed by value 1, at `n` = 1. That is,
 * the sequence is defined by
 * \f[
 * F_n = \left\{\begin{array}{ll}
 *     0                 & \text{if } n=0, \\
 *     1                 & \text{if } n=1\text{, and} \\
 *     F_{n-2} + F_{n-1} & \text{if } n>1.
 *   \end{array}\right.
 * \f]
 */
// #### Definição
//
// Esta implementação segue a estratégia mais comum das soluções recursivas:
// decompor o problema em problemas mais simples, resolver esses problemas mais
// simples usando exactamente a mesma estratégia, recursivamente, e compor as
// soluções dos subproblemas de modo a obter a solução do problema como um todo.
// Uma solução recursiva, como esta, precisa de possuir casos de paragem (ou
// casos especiais), para os quais a solução é imediata, não sendo necessária
// qualquer decomposição adicional. A definição recursiva da sucessão de
// Fibonacci aparenta adequar-se bem a esta estratégia:
//
// ![F(n)={0, se n = 0, 1, se n = 1, e F(n-2) + F(n-1), se n > 
// 1}](http://bit.ly/169sagW)
long stupidly_recursive_fibonacci(int n)
{
	// Em primeiro lugar, verificamos as pré-condições e lidamos com as
	// violações que forem detectadas.
	assert(n >= 0);
	assert(n <= MAXIMUM_TERM_FITTING_A_LONG);

	// Depois, lidamos com os dois casos especiais da sucessão. Estes casos
	// servem também para garantir que as invocações recursivas desta função
	// acabarão sempre por terminar (em tempo finito).
	if (n == 0)
		return 0L;
	if (n == 1)
		return 1L;

	// O caso geral é simplesmente a devolução da soma dos termos anterior
	// da sucessão. Para os obter, invocamos a própria função com os dois
	// valores inteiros anteriores a `n`. O problema desta implenentação é
	// que se está a reduzir o problema de calcular
	// ![F(n)](http://bit.ly/ZCdcqY) aos subproblemas de calcular
	// ![F(n-2)](http://bit.ly/14HrTAK) e de calcular
	// ![F(n-1)](http://bit.ly/13V2Vid), _mas estes subproblemas não são
	// independentes!_ Isso faz com que esta implementação seja muitíssimo
	// ineficiente.
	return stupidly_recursive_fibonacci(n - 2)
		+ stupidly_recursive_fibonacci(n - 1);
}

// Para compreendemos bem a ineficiência desta implementação, vamos calcular
// alguns valores interessantes.
//
// Em primeiro lugar, uma revelação: a sucessão de Fibonacci pode ser expressa
// de forma fechada. «Estamos aqui com tudo isto e a coisa resume-se a uma
// fórmula fechada?», podem perguntar. Sim. Mas pode haver boas razões para não
// recorrer a essa fórmula: ela obriga-nos a trabalhar com valores de vírgula
// flutuante e, por isso, a lidar com as correspondentes limitações de precisão.
// As nossas implementações, recorrendo a _long_, são exactas... Podem encontrar
// informação sobre a sucessão de Fibonacci em vários locais. Recomendo os
// seguintes:
//
// - [F_n](http://www.wolframalpha.com/input/?i=F_n) no
// [Wolfram|Alpha](http://www.wolframalpha.com/) - O Wolfram|Alpha é um motor
// de pesquisa com a [Wolfram](http://www.wolfram.com/) por trás (a mesma que
// produz o maravilhoso
// [Wolfram|Mathematica](http://www.wolfram.com/mathematica/)) só podia ser
// excelente. E é-o.
//
// - [Fibonacci Number](http://mathworld.wolfram.com/FibonacciNumber.html) no
// [Wolfram|MathWorld](http://mathworld.wolfram.com/) - O Wolfram|MathWorld é
// uma enciclopédia matemática também com a garantia de qualidade da
// [Wolfram](http://www.wolfram.com/). Outra excelente fonte de informação.
//
// - [Fibonacci number](http://en.wikipedia.org/wiki/Fibonacci_number) na
// [Wikipédia](http://en.wikipedia.org/).
//
// A forma fechada da sucessão de Fibonacci é
//
// ![F_n=(phi^n - psi^n)/sqrt(5)](http://bit.ly/10fxJ6c),
//
// onde
//
// ![phi=(1+sqrt(5))/2](http://bit.ly/15hTKsW), que é chamado _número de ouro_,
// e
//
// ![psi=(1-sqrt(5))/2](http://bit.ly/12Elq43).
//
// Outra forma fechada é
//
// ![F_n=arred(phi^n/sqrt(5))](http://bit.ly/1254VAx),
//
// onde
//
// ![arred(x)](http://bit.ly/10bSbcU)
//
// é a função que resulta no inteiro mais próximo ou arredondamento de
// ![x](http://bit.ly/12ElMrk), sendo que em caso de empate entre dois inteiros
// mais próximos se escolhe o inteiro que for par.
//
// Ambas as formas mostram bem o que já tínhamos observado: o crescimento da
// sucessão de Fibonacci é extremamente rápido. Mais precisamente, o crescimento
// da sucessão de Fibonacci é _exponencial_, sendo a base da exponencial o
// número de ouro e o expoente o número do termo da sucessão.
//
// Vamos agora calcular o número de invocações da função `recursive_fibonacci()`
// que ocorrem durante a cálculo de um dado termo ![n](http://bit.ly/Z4ELdk) da
// sucessão de Fibonacci, ou seja, durante a execução da função que acabámos de
// definir quando se lhe passa como argumento esse valor
// ![n](http://bit.ly/Z4ELdk). Chamemos a esse número de invocações
// ![N_n](http://bit.ly/139Mk7p).
//
// Em primeiro lugar, é evidente que invocar `recursive_fibonacci()` com
// ![n](http://bit.ly/Z4ELdk) como argumento leva a uma invocação inicial,
// nomeadamente a que acabámos de referir, com ![n](http://bit.ly/Z4ELdk) como
// argumento. Se o valor de ![n](http://bit.ly/Z4ELdk) for 0 ou 1, então não é
// realizada qualquer outra invocação. Ou seja, ![N_n=1](http://bit.ly/YwMaHD)
// quando ![n=0](http://bit.ly/10afb7o) ou ![n=1](http://bit.ly/14HsgeM). Se o
// valor de ![n](http://bit.ly/Z4ELdk) for maior que 1, então a função será
// invocada recursivamente com os valores ![n-2](http://bit.ly/18mQyLi) e
// ![n-1](http://bit.ly/10fBCrR) como argumento, o que resultará num total de
// ![1+N_n-2+N_n-1](http://bit.ly/Zxxpzv) invocações. Ou seja, o número de
// invocações recursivas da função pode ser expresso também de forma recursiva:
//
// ![definição recursiva de N_n](http://bit.ly/125adMb)
//
// Esta definição é muito parecida com a definição recursiva da própria sucessão
// de Fibonacci. De facto, é fácil demonstrar que ![N_n =
// 2F_n+1-1](http://bit.ly/10zTgWa). Ou seja, o número de invocações cresce
// exponencialmente, tal como a própria sucessão de Fibonacci! Não admira que
// esta implementação seja absolutamente inaceitável...
//
// Já agora, podemos também calcular o número de somas realizadas. Seja
// ![S_n](http://bit.ly/13g3vTT) o número de somas realizadas quando se invoca
// `recursive_fibonacci()` com o argumento ![n](http://bit.ly/Z4ELdk). É fácil
// ver que, quando ![n](http://bit.ly/Z4ELdk) é 0 ou 1, a invocação de
// `recursive_fibonacci()` resulta em 0 somas. Quando se invoca com
// ![n](http://bit.ly/Z4ELdk) maior que 1, realiza-se uma soma dos resultados
// das invocações recursivas com os valores ![n-2](http://bit.ly/18mQyLi) e
// ![n-1](http://bit.ly/10fBCrR) como argumento, o que resultará num total de
// ![1+S_n-2+S_n-1](http://bit.ly/YnkQcQ) somas. Ou seja, o número de somas
// realizadas durante a invocação da função pode ser expresso também de forma
// recursiva:
//
// ![definição recursiva de S_n](http://bit.ly/13VO8Ql)
//
// Esta definição é também muito parecida com a definição recursiva da própria
// sucessão de Fibonacci. De facto, é fácil demonstrar que ![S_n =
// F_n+1-1](http://bit.ly/139Tdpr). Ou seja, o número de somas cresce
// exponencialmente, tal como a própria sucessão de Fibonacci! Isto quando uma
// implementação iterativa trivial precisa de 0 somas para calcular o termo 0 da
// sucessão e de ![n-1](http://bit.ly/10fBCrR) somas para calcular o termo
// ![n](http://bit.ly/Z4ELdk) quando ![n>0](http://bit.ly/ZteSVa). Mais uma vez,
// não admira que esta implementação seja absolutamente inaceitável.
//
// A moral desta estória não é que a recursividade seja naturalmente perversa.
// Não o é. As soluções recursivas podem ser tão eficientes quanto as soluções
// iterativas. O problema aqui não é a recursividade em si, mas o algoritmo
// usado.
  
// ### Implementação recursiva com _lookup_

// #### Documentação
/** \brief Returns the `n`th term of the Fibonacci sequence.
 *
 * \param n The number of the term to return (first valid value is 0).
 * \return The value of the `n`th term of the Fibonacci sequence. The time taken
 * by the function grows !!!!!!!!!!!!!!!!!!!! with `n`.
 * \pre `n` ≥ 0
 * \post result = \f$F_{\mathtt{n}}\f$
 *
 * Returns the `n`th term of the Fibonacci sequence. It is assumed the sequence
 * starts at `n` = 0, with value 0, followed by value 1, at `n` = 1. That is,
 * the sequence is defined by
 * \f[
 * F_n = \left\{\begin{array}{ll}
 *     0                 & \text{if } n=0, \\
 *     1                 & \text{if } n=1\text{, and} \\
 *     F_{n-2} + F_{n-1} & \text{if } n>1.
 *   \end{array}\right.
 * \f]
 */
// #### Definição
long recursive_fibonacci(int n)
{
	assert(n >= 0);
	assert(n <= MAXIMUM_TERM_FITTING_A_LONG);

	// Esta implementação evita os cálculos repetidos dos mesmos termos da
	// sucessão de Fibonacci usando uma memória auxiliar. A ideia é calcular
	// cada termo da sucessão uma única vez, guardar o seu valor em memória
	// e, das próximas vezes que o termo for solicitado, usar o valor
	// guardado em memória. Isto implica, naturalmente, que a memória usada
	// persista para além do âmbito restrito de uma execução da função. Ou
	// seja, não podemos de forma nenhuma usar variáveis locais
	// _automáticas_, pois estas são construídas quando a instrução que as
	// define é executada, e destruídas quando se atinge o final do bloco
	// onde a sua definição se encontra. Em vez de partir daqui as variáveis
	// globais, cujo tempo de vida abarca todo o tempo de execução do
	// programa, e que são visíveis em todo o programa, preferimos usar
	// variáveis locais _estáticas_. Estas variáveis definem-se usando o
	// _qualificador_ `static`, duram desde a execução da instrução que as
	// define até o final do programa e têm a mesma visibilidade restrita
	// que qualquer variável local tem. Note-se que a instrução de definição
	// de qualquer variável local estática é executada uma única vez,
	// nomeadamente a primeira vez que o fluxo de execução do programa passa
	// por essa instrução. A partir daí a instrução de definição, com a
	// respectiva inicialização, é ignorada. Logo, a inicialização de uma
	// variável local estática _é feita uma única vez_ durante a execução do
	// programa.
	//
	// Uma vez que o número de termos da sucessão de Fibonacci calculáveis
	// através desta função é limitado, dado que ela devolve valores `long`,
	// só se podendo calcular o valor dos termos entre 0 e
	// `MAXIMUM_TERM_FITTING_A_LONG`, podemos reservar espaço para todos os
	// termos num _array_ `F` de `long`. A utilização de uma macro
	// `MAXIMUM_TERM_FITTING_A_LONG` na expressão para cálculo do
	// comprimento do _array_ permite-nos usar inicializadores do C. Dessa
	// forma, podemos inicializar a memória dos termos da sucessão de
	// Fibonacci com os dois primeiros termos dessa sucessão, que têm os
	// valores 0 e 1, respectivamente, correspondentes aos termos com
	// índices 0 e 1.
	static long F[MAXIMUM_TERM_FITTING_A_LONG + 1] = {0, 1};
	// Não basta definir o espaço de memória dos termos da sucessão: é
	// necessário definir uma variável que guarde em cada instante quantos
	// termos estão já calculados. Neste caso inicializa-se a variável com o
	// valor 2, uma vez que se inicializou a memória com os dois primeiros
	// termos da sucessão de Fibonacci.
	static int number_of_calculated_terms = 2;

	// Estamos agora preparados para indagar o valor do termo da sucessão de
	// Fibonacci solicitado. Se o termo já constar na memória de termos
	// calculados, i.e., se o valor `n` for inferior a
	// `number_of_calculated_terms` limitamo-nos a devolver o valor
	// memorizado.
	if (n < number_of_calculated_terms)
		return F[n];

	// O caso geral passa por
	//
	// 1. invocar recursivamente a própria função para obter os termos `n -
	// 2` e `n - 1`,
	//
	// 2. calcular o termo `n` como soma dos dois termos anteriores
	// calculados,
	//
	// 3. guardar esse novo termo na memória, de modo a não precisar de ser
	// recalculado, e
	//
	// 4. terminar a função, devolvendo o valor do novo termo ao retornar ao
	// ponto de invocação da função.
	//
	// Estes passos estão condensados em apenas duas linhas de código. Essa
	// condensação seria considerada uma má prática em quase todas as
	// linguagens de programação, mas este tipo de código é idiomático em C,
	// pelo que preferimos apresentá-lo desta forma. Seja como for, uma
	// forma ortodoxa de escrever este código seria:
	//
	// ```C
	// F[n] = recursive_fibonacci(n - 2) + recursive_fibonacci(n - 1);
	// number_of_calculated_terms++;
	//
	// return F[n];
	// ```
	//
	// Alternativamente, podemos considerar que o caso especial é aquele em
	// que o termo pretendido _não_ foi ainda calculado, o que nos levaria
	// ao seguinte código, bem mais legível, que substitui não apenas as
	// duas últimas linhas do código apresentado, mas também as duas
	// anteriores:
	//
	// ```C
	// if (number_of_calculated_terms <= n) {
	//         F[n] = recursive_fibonacci(n - 2) + 
	//                recursive_fibonacci(n - 1);
	//         number_of_calculated_terms++;
	// }
	//
	// return F[n];
	// ```
	number_of_calculated_terms++;
	return F[n] = recursive_fibonacci(n - 2) + recursive_fibonacci(n - 1);
}

// ### Implementação recursiva com _lookup_ usando TAD

// #### Documentação
/** \brief Returns the `n`th term of the Fibonacci sequence.
 *
 * \param n The number of the term to return (first valid value is 0).
 * \return The value of the `n`th term of the Fibonacci sequence. The time taken
 * by the function grows !!!!!!!!!!!!!!!!!!!! with `n`.
 * \pre `n` ≥ 0
 * \post result = \f$F_{\mathtt{n}}\f$
 *
 * Returns the `n`th term of the Fibonacci sequence. It is assumed the sequence
 * starts at `n` = 0, with value 0, followed by value 1, at `n` = 1. That is,
 * the sequence is defined by
 * \f[
 * F_n = \left\{\begin{array}{ll}
 *     0                 & \text{if } n=0, \\
 *     1                 & \text{if } n=1\text{, and} \\
 *     F_{n-2} + F_{n-1} & \text{if } n>1.
 *   \end{array}\right.
 * \f]
 */
// #### Definição
long recursive_fibonacci_using_ADT(int n)
{
	assert(n >= 0);
	assert(n <= MAXIMUM_TERM_FITTING_A_LONG);

	// Em vez de se um _array_ de `long` como memória para os termos já
	// calculados da sucessão de Fibonacci, bem como um inteiro indicando a
	// quantidade de termos memorizados, recorremos aqui ao TAD sucessão de
	// `long`, representado pela estrutura `struct sequence_of_longs`. No
	// caso particular da sequência se Fibonacci, a utilização deste TAD não
	// traz grandes vantagens face à utilização de um _array_, dada a
	// pequena quantidade de termos da sucessão representáveis no tipo
	// _long_. No entanto, é um bom exercício recorrer aqui ao TAD,
	// exercício que nos pode ser útil noutros casos em que o
	// dimensionamento _a priori_ do _array_ não seja tão fácil.
	//
	// Tal como definido o TAD, o código cliente só pode trabalhar com as
	// sucessões através de ponteiros. Assim, precisamos de definir uma
	// variável local _estática_ (de modo a que o seu valor persiste entre
	// invocações da função `recursive_fibonacci_using_ADT`). Dadas as
	// restrições do C, não podemos usar o construtor `SEQL_new()`
	// directamente na inicialização, que tem de ser feita usando uma
	// _expressão constante_. Assim, optámos por inicializar o ponteiro `F`
	// com o valor especial `NULL`.
	static struct sequence_of_longs *F = NULL;

	// Dada a inicialização do ponteiro com `NULL`, podemos agora detectar o
	// seu valor inicial `NULL` para lhe atribuir o endereço de uma nova
	// estrutura `struct sequence_of_longs` construída de forma dinâmica
	// através do construtor `SEQL_new()`. Este código é executado sempre
	// que a função é invocada, o que é uma infelicidade, mas não há forma
	// de o evitar, dado que não é possível inicializar o ponteiro `F` para
	// a sucessão de `long` com o valor devolvido pela função `SEQL_new()`.
	//
	// Outro problema associado às limitações do C é o da libertação de
	// memória. O C não fornece nenhum mecanismo para executar código no
	// contexto das variáveis locais estáticas no final do programa de modo
	// a podermos «arrumar a casa», ou seja, libertar recursos que lhes
	// estejam associados. Neste caso os recursos são apenas duas variáveis
	// dinâmicas: (a) a `struct sequence_of_long` apontada por `F` e
	// (embora, como clientes, não o devêssemos precisar de saber) e (b) o
	// _array_ dinâmico usado internamente pelo TAD para guardar os termos.
	// Como toda a memória dinâmica associada ao programa em execução é
	// libertada durante a sua terminação, a nossa violação do princípio de
	// que quem reserva memória explicitamente a deve também libertar
	// explicitamente não é dramática.
	if (F == NULL)
		F = SEQL_new();

	// Se o termo já constar na sucessão de `long` com os termos da sucessão
	// de Fibonacci já calculados, limitamo-nos a devolvê-lo.
	if (n < SEQL_length(F))
		return SEQL_term(F, n);

	// Se o termo não está ainda calculado, há que fazê-lo. Uma vez que,
	// depois de o calcular, teremos de o adicionar à memória e devolver,
	// definimos uma variável `F_n` para guardar o valor calculado. Uma vez
	// que o valor usado para inicializar esta variável depende do valor de
	// `n`, usamos o operador `?:` do C para discriminar entre as três
	// diferentes formas de inicialização, evitando ter de recorrer a uma
	// definição sem inicialização seguida de duas instruções de selecção
	// encadeadas:
	//
	// ```C
	// long F_n;
	// if (n == 0)
	//         F_n = 0L;
	// else if (n == 1)
	//         F_n = 1L;
	// else
	//         F_n = recursive_fibonacci_using_ADT(n - 2) + 
	//               recursive_fibonacci_using_ADT(n - 1);
	// ```
	long F_n = n == 0 ? 0L : n == 1 ? 1L :
		recursive_fibonacci_using_ADT(n - 2) + 
		recursive_fibonacci_using_ADT(n - 1);

	// Agora que já temos o valor de `F_n` calculado, devemos guardá-lo em
	// memória, na nossa sucessão de `long`, de modo a não precisar de ser
	// calculado de novo.
	SEQL_add(F, F_n);

	// Finalmente, devolvemos o valor calculado.
	return F_n;
}

// ###Implementação recursiva eficiente sem memória

// #### Função auxiliar
long tr_fibonacci(int n, int previous_value, int value)
{
    if (n == 1)
        return value;

    return tr_fibonacci(n - 1, value, previous_value + value);
}

// #### Documentação
/** \brief Returns the `n`th term of the Fibonacci sequence.
 *
 * \param n The number of the term to return (first valid value is 0).
 * \return The value of the `n`th term of the Fibonacci sequence. The time taken
 * by the function grows !!!!!!!!!!!!!!!!!!!! with `n`.
 * \pre `n` ≥ 0
 * \post result = \f$F_{\mathtt{n}}\f$
 *
 * Returns the `n`th term of the Fibonacci sequence. It is assumed the sequence
 * starts at `n` = 0, with value 0, followed by value 1, at `n` = 1. That is,
 * the sequence is defined by
 * \f[
 * F_n = \left\{\begin{array}{ll}
 *     0                 & \text{if } n=0, \\
 *     1                 & \text{if } n=1\text{, and} \\
 *     F_{n-2} + F_{n-1} & \text{if } n>1.
 *   \end{array}\right.
 * \f]
 */
// #### Definição
long tail_recursive_fibonacci(int n)
{
    if (n == 0)
        return 0;

    return tr_fibonacci(n, 0, 1);
}

// ### Implementação iterativa

// #### Documentação
// A documentação da função é feita no formato do
// [Doxygen](http://doxygen.org/), como habitualmente.
/** \brief Returns the `n`th term of the Fiboncci sequence.
 *
 * \param n The number of the term to return (first valid value is 0).
 * \return The value of the `n`th term of the Fibonacci sequence. The time taken
 * by the function grows linearly with `n`.
 * \pre `n` ≥ 0
 * \post result = \f$F_{\mathtt{n}}\f$
 *
 * Returns the `n`th term of the Fibonacci sequence. It is assumed the sequence
 * starts at `n` = 0, with value 0, followed by value 1, at `n` = 1. That is,
 * the sequence is defined by
 * \f[
 * F_n = \left\{\begin{array}{ll}
 *     0                 & \text{if } n=0, \\
 *     1                 & \text{if } n=1\text{, and} \\
 *     F_{n-2} + F_{n-1} & \text{if } n>1.
 *   \end{array}\right.
 * \f]
 */
// #### Definição
long iterative_fibonacci(int n)
{
	assert(n >= 0);
	assert(n <= MAXIMUM_TERM_FITTING_A_LONG);

	if (n == 0)
		return 0L;
	if (n == 1)
		return 1L;

	long previous_term = 1L;
	long current_term = 1L;
	for(int i = 2; i != n; i++) {
		current_term += previous_term;
		previous_term = current_term - previous_term;
	}

	return current_term;
}

// ### Procedimento !!!!!!!

// #### Documentação
// !!!!!!!!
/** \brief !!!!!!!!!!!! (includes month 0)
 *
 * \param n !!!!!!!!!
 * \return !!!!!!!!!!!
 * \pre `n` ≥ 0
 * \post !!!
 *
 * !!!!!!!!!!!!!!!
 */
// #### Definição
void experiment_efficiency_of(char title[], long fibonacci(int),
			int last_term)
{
	printf("%s\n", title);
	double previous_time = 0.0;
	for (int n = 0; n != last_term + 1; n++) {
		clock_t start = clock();
		int f = fibonacci(n);
		clock_t end = clock();
		double time = (double) (end - start) / CLOCKS_PER_SEC;
		printf("f(%d) = %d in %.4fs %g\n", n, f, time,
			time / previous_time);
		previous_time = time;
	}
}

// ### Procedimento !!!!!!!
//
// !!!!!!!!
int main(void)
{
	for (int n = 0; n != MAXIMUM_TERM_FITTING_A_LONG + 1; n++) {
//		printf("F(%d) [stupid recursive] = %ld\n", n, stupidly_recursive_fibonacci(n));
		printf("F(%d) [recursive         ] = %ld\n", n, recursive_fibonacci(n));
		printf("F(%d) [recursive with ADT] = %ld\n", n, recursive_fibonacci_using_ADT(n));
		printf("F(%d) [iterative         ] = %ld\n", n, iterative_fibonacci(n));
		putchar('\n');
	}

	experiment_efficiency_of("Stupidly recursive implementation of the fibonacci sequence:",
				stupidly_recursive_fibonacci, 35);
	experiment_efficiency_of("Recursive implementation of the fibonacci sequence:",
				recursive_fibonacci, 35);
	experiment_efficiency_of("Recursive implementation of the fibonacci sequence using ADT for storage:",
				recursive_fibonacci_using_ADT, 35);
	experiment_efficiency_of("Three variable iterative implementation of the fibonacci sequence:",
				iterative_fibonacci, 35);

	return EXIT_SUCCESS;
}
