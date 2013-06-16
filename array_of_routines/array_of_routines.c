// `array_of_routines.c` &ndash; Ponteiros para rotinas e _arrays_
// ===============================================================
//
// Este programa ilustra uma forma particular de usar [ponteiros para
// rotinas](routine_pointers.c.html): guardando-os dentro de um _array_. Para
// informação especificamente sobre ponteiros para rotinas, sua utilização e
// particularidades da sua implementação na linguagem C, ver
// [routine_pointers.c](routine_pointers.c.html).
//
// Optámos por omitir os comentários de documentação do [Doxygen](doxygen.org),
// ao contrário do que tem sido nosso hábito.

// Inclusões
// ---------
//
// As inclusões usuais de ficheiros de cabeçalho, para poder usar o procedimento
// `printf` de escrita no ecrã e para poder devolver `EXIT_SUCCESS` no final do
// programa.
#include <stdio.h>
#include <stdlib.h>

// Definição das rotinas a guardar no _array_
// ------------------------------------------
//
// Todos os itens de um _array_ em C têm de ser do mesmo tipo. Neste caso o
// _array_ guardará ponteiros para rotinas, que pode isso precisam de ter todos
// o mesmo tipo. Ora, o tipo de um ponteiro para um rotina inclui a _assinatura_
// completa da rotina, com excepção dos nomes da rotina e dos seus parâmetros.
// Ou seja, inclui:
//
// - A sequência dos tipos dos parâmetros da rotina.
// - O tipo de devolução da rotina.
//
// No nosso caso, todas as rotinas serão funções com dois parâmetros do tipo
// `int` e devolvendo também um `int`. Tratando-se de um mero exemplo, optámos
// por guardar no _array_ apenas quatro funções, correspondendo às quatro
// operações aritméticas básicas.

// ### Definição da função `sum()`
//
// Devolve a soma dos seus dois argumentos.
int sum(int first, int second)
{
	return first + second;
}

// ### Definição da função `subtraction()`
//
// Devolve a diferença entre os seus dois argumentos.
int subtraction(int first, int second)
{
	return first - second;
}

// ### Definição da função `product()`
//
// Devolve o produto dos seus dois argumentos.
int product(int first, int second)
{
	return first * second;
}

// ### Definição da função `product()`
//
// Devolve o quociente do seu primeiro argumento quando dividido pelo seu
// segundo argumento.
int division(int first, int second)
{
	return first / second;
}

// Definição do _array_ de operações
// ---------------------------------
//
// O _array_ será definido de forma a ser constante e global. A opção pela
// constância do _array_ prende-se com o seu carácter global. É que, se a
// utilização de variáveis globais é geralmente um má prática, por introduzir
// formas subtis e pouco evidentes de comunicação entre troços distantes de um
// programa, já a utilização de constantes globais não sofre do mesmo problema,
// sendo por isso a sua utilização aconselhável em muitas circunstâncias.
//
// A definição do _array_ de ponteiros para as funções definidas é difícil de
// perceber, devido à sintaxe peculiar do C. Há, no entanto, uma forma de
// interpretação que torna a tarefa de compreender esta definição bem mais
// simples: a definição de uma entidade em C reflecte a sua utilização no resto
// do código. Por exemplo, se definirmos uma variável `an_int` como sendo do
// tipo `int`, então poderemos usá-la no código, por exemplo, numa atribuição a
// uma outra variável do mesmo tipo, da seguinte forma:
//
// ```C
// // Definition of another_int and an_int...
// ...
// // Use of the variables:
// another_int = an_int;
// ```
//
// Ou seja, escrevendo `an_int` obtemos num `int`. A definição de `an_int`
// reflecte esse facto: começa por se dizer o tipo resultante, neste caso `int`,
// escreve-se depois a expressão que resulta nesse tipo, neste caso simplesmente
// `an_int`, e finalmente termina-se a instrução de definição com o terminador
// `;`:
//
// ```C
// int an_int;
// ```
//
// ou, procedendo a uma inicialização durante a definição da variável,
//
// ```C
// int an_int = 3;
// an_int = 0; // valid: assignment changing the the value of the variable.
// ```
//
// Se em vez de uma variável pretendêssemos uma constante `a_constant_int`,
// bastaria dizer que a expressão de `a_constant_int` resultaria num inteiro
// constante:
//
// ```C
// int const a_constant_int = 3;
// a_constant_int = 0; // invalid: cannot change a constant!
// ```
//
// O C permite trocar a posição do qualificador `const`, que se pode colocar,
// por isso, na sua posição mais habitual:
//
// ```C
// const int a_constant_int = 3;
// a_constant_int = 0; // invalid: cannot change a constant!
// ```
//
// Suponha-se agora uma variável `pointer_to_an_int` que é um ponteiro para
// `int`, ou seja, que guarda o endereço de um `int`. Assumindo que a variável
// contém um endereço válido, como se pode aceder ao inteiro por ela apontado?
// Fácil: usando o operador conteúdo, ou de «desreferenciação», `*`. Por
// exemplo:
//
// ```C
// // Definition and initialization of an_int:
// int an_int = 3;
// // Definition of pointer_to_an_int:
// ...
// // Assignment of the address of an_int to the pointer pointer_to_an_int:
// pointer_to_an_int = &an_int;
// // Definition of another_int:
// int another_int;
// // Assignment of the contents of the integer pointed by pointer_to_an_int
// // to variable another_int: 
// another_int = *pointer_to_an_int;
// ```
//
// Ou seja, escrevendo `*pointer_to_an_int` obtemos um `int`. A definição de
// `pointer_to_an_int` reflecte esse facto: começa por se dizer o tipo
// resultante, neste caso `int`, escreve-se depois a expressão que resulta nesse
// tipo, neste caso `*pointer_to_an_int`, e finalmente termina-se a instrução
// de definição com o terminador `;`:
//
// ```C
// int *pointer_to_an_int;
// ```
//
// ou, procedendo a uma inicialização durante a definição da variável,
//
// ```C
// int *pointer_to_an_int = &an_int;
// pointer_to_an_int = &some_other_int; // valid: assignment changes pointer.
// ```
//
// Se em vez de uma variável pretendêssemos uma constante
// `constant_pointer_to_an_int`, bastaria dizer que a expressão
// `constant_pointer_to_an_int` resultaria num ponteiro constante para `int`:
//
// ```C
// int *const constant_pointer_to_an_int = &an_int;
// constant_pointer_to_an_int =
//         &some_other_int; // invalid: cannot change the constant pointer!
// ```
//
// Estranho? Nem por isso. Como queremos que `constant_pointer_to_an_int` seja
// um ponteiro constante para `int`, temos de colocar o qualificador após o `*
// `. Se colocássemos o qualificador `const` antes do `*` estaríamos a dizer que
// a expressão `*constant_pointer_to_an_int` tinha o tipo `int const` (ou `const
// int`, que é o mesmo). Ou seja, estaríamos a dizer que o ponteiro em si era
// variável, mas apontava para `int` constantes, que é como quem diz que os
// `int` apontados não poderiam ser alterados através do ponteiro. Vamos
// experimentar? Aqui vai:
//
// ```C
// const int *pointer_to_a_constant_int = &an_int;
// *pointer_to_a_constant_int =
//         0; // invalid: cannot change pointed constant int.
// pointer_to_a_constant_int =
//         &some_other_int; // valid: assignment changes pointer.
// ```
//
// Podemos mesmo combinar as duas formas e definir um ponteiro constante para um
// `int` constante:
//
// ```C
// const int *const constant_pointer_to_a_constant_int = &an_int;
// *constant_pointer_to_a_constant_int =
//         0; // invalid: cannot change pointed constant int.
// constant_pointer_to_a_constant_int =
//         &some_other_int; // invalid: cannot change the constant pointer!
// ```
//
// Suponha-se agora que pretendemos definir um _array_ de 10 `int` chamado
// `ten_ints`. Depois de o definir, podemos usá-lo em expressões de indexação,
// obtendo-se inteiros no processo:
//
// ```C
// // Definition of ten_ints with values 20 down to 11:
// ...
// // Definition of an_int:
// int an_int;
// // Assignment of the value of the first int in array ten_ints to variable
// // an_int:
// an_int = ten_ints[0];
// ```
//
// Ou seja, escrevendo `ten_ints[`_n_`]`, com _n_ entre 0 e 9, obtemos um `int`.
// A definição de `ten_ints` reflecte esse facto: começa por se dizer o tipo
// resultante, neste caso `int`, escreve-se depois a expressão que resulta nesse
// tipo, neste caso `ten_ints[10]`, e finalmente termina-se a instrução de
// definição com o terminador `;`. Tratando-se da definição de um _array_, o que
// colocamos dentro dos parênteses rectos é o número de itens do _array_, ou
// seja, o seu comprimento:
//
// ```C
// int ten_ints[10];
// ```
//
// ou, procedendo a uma inicialização durante a definição do _array_,
//
// ```C
// int ten_ints[10] = {
//         20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 11
// };
// ten_ints[0] = 0; // valid: assignment changes first item.
// ```
//
// Usando-se um inicializador, podemos deixar a tarefa de contar o número de
// itens ao compilador. Assim, poderíamos ter definido o _array_ como se segue:
//
// ```C
// int ten_ints[] = {
//         20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 11
// };
// ```
//
// Se se pretender que os itens de um _array_ `ten_constant_ints` sejam
// constantes, ou seja, que as expressões `ten_constant_ints[`_n_`]` sejam do
// tipo `const int`, então temos de definir o _array_ como se segue:
// ```C
// const int ten_constant_ints[10] = {
//         20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 11
// };
// ten_constant_ints[0] = 0; // invalid: cannot change the array items!
// ```
//
// Finalmente, suponhamos uma variável `pointer_to_funtion` que guarda o
// endereço de uma função com dois parâmetros do tipo `int` e que devolve também
// um `int`. Para invocar a função apontada por esta variável com os argumentos
// 2 e 3, por exemplo, temos de (a) desreferenciar o ponteiro usando o operador
// `*` e (b) invocar a função resultante usando o operador de invocação, que
// consiste num par de parênteses curvos `()` contendo a lista dos argumentos
// separados por vírgulas. Como o operador de invocação `()` tem precedência
// relativamente ao operador de desreferenciação `*` (ver [tabela de precedência
// e associatividade dos operadores do C e do C++ na
// Wikipédia](http://bit.ly/147TVC2)), temos de garantir que este último é
// aplicado ao ponteiro para a função antes do operador de invocação. Ou seja,
// temos de escrever `(*pointer_to_function)(2, 3)`. O resultado desta invocação
// é um `int`, uma vez que dissemos que a função tem dois parâmetros `int` e
// devolve também um `int`. Por exemplo:
//
//
// ```C
// // Definition of the sum() function:
// int sum(int first, int second)
// {
//         return first + second;
// }
//
// // Definition of the subtraction() function:
// int subtraction(int first, int second)
// {
//         return first - second;
// }
//
// // Definition of pointer_to_function pointing to the sum() function:
// ...
// // Definition of an_int:
// int an_int;
// // Assignment of the result of the call to the sum function with arguments
// // 2 and 3 through the pointer_to_function variable:
// an_int = (*pointer_to_function)(2, 3);
// ```
//
// Ou seja, escrevendo `(*pointer_to_function)(`_n_`, `_m_`)`, com _n_ e _m_
// valores inteiros, obtemos um `int`. A definição de `pointer_to_function`
// reflecte esse facto: começa por se dizer o tipo resultante, neste caso `int`,
// escreve-se depois a expressão que resulta nesse tipo, neste caso
// `(*pointer_to_function)(int, int)`, e finalmente termina-se a instrução de
// definição com o terminador `;`. Tratando-se da definição de um ponteiro para
// uma rotina, o que colocamos dentro dos parênteses curvos no local dos
// argumentos é o tipo de cada um dos parâmetros da rotina:
//
// ```C
// int (*pointer_to_function)(int, int);
// ```
//
// ou, procedendo a uma inicialização durante a definição do ponteiro,
//
// ```C
// int (*pointer_to_function)(int, int) = &sum;
// pointer_to_function = &subtraction; // valid: assignment changes pointer.
// *pointer_to_function = ...; // invalid: routines are unchangeable.
// ```
//
// O C é simpático, assumindo que qualquer referência ao nome de uma rotina na
// realidade se refere ao endereço dessa rotina. Assim, o código acima pode ser
// simplificado:
//
// ```C
// int (*pointer_to_function)(int, int) = sum;
// pointer_to_function = subtraction; // valid: assignment changes pointer.
// ```
//
// Se pretendermos definir uma constante `constant_pointer_to_function`, então
// teremos de preceder o nome da constante do qualificador `const`, da mesma
// forma que anteriormente:
//
// ```C
// int (*const constant_pointer_to_function)(int, int) = sum;
// pointer_to_function =
//         subtraction; // invalid: cannot change a constant pointer.
// ```
//
// Estamos finalmente em condições de perceber como definir o nosso _array_ de
// quatro ponteiros _constantes_ para funções com dois parâmetros `int` e
// devolvendo um `int`. Suponhamos que este _array_ se chama `operators` e que o
// seu primeiro item é o ponteiro (constante) para a função `sum()`. Então as
// seguintes expressões têm os significados indicados:
//
// - `operators` - O _array_ completo (que o C, salvo raras excepções, considera
//   como equivalente a um ponteiro para o seu primeiro item).
//
// - `operators[0]` - O primeiro item do _array_, que é um ponteiro para a
//   função `sum()`.
//
// - `*operators[0]` - O conteúdo da posição de memória apontada pelo primeiro
//   item do _array_, ou seja, a função `sum()` propriamente dita.
//
// - `(*operators[0])(2, 3)` - O resultado da invocação da função `sum()`
//   apontada pelo primeiro item do _array_ passando-lhe os argumentos 2 e 3, ou
//   seja, o valor 5. Note-se que a colocação dos parênteses curvos em torno de
//   `*operators[0]` é necessária porque o operador de invocação `()`, usado
//   neste caso com os operandos 2 e 3, _tem maior precedência que o operador
//   `*`_ (ver [tabela de precedência e associatividade dos operadores do C e do
//   C++ na Wikipédia](http://bit.ly/147TVC2)).
//
// Ou seja, escrevendo `(*operators[`_i_`])(`_n_`, `_m_`)`, com _i_ entre 0 e 3
// e com _n_ e _m_ valores inteiros, obtemos um `int`. A definição de
// `operators` reflecte esse facto: começa por se dizer o tipo resultante, neste
// caso `int`, escreve-se depois a expressão que resulta nesse tipo, neste caso
// `(*operators[4])(int, int)`, e finalmente termina-se a instrução de definição
// com o terminador `;`. Tratando-se da definição de um _array_, colocamos entre
// parênteses rectos o número de itens do _array_, neste caso 4. Tratando-se de
// um _array_ de ponteiros para rotinas, o que colocamos dentro dos parênteses
// curvos no local dos argumentos é o tipo de cada um dos parâmetros da rotina,
// neste caso dois `int`:
//
// ```C
// int (*operations[4])(int, int);
// ```
//
// Uma vez que desejamos que os itens do _array_ (os ponteiros) sejam
// constantes, colocamos o qualificador `const` entre o `*` e o nome do _array_:
//
// ```C
// int (*const operations[4])(int, int);
// ```
//
// Podemos inicializar o _array_ usando um inicializador com os endereços das
// várias funções:
//
// ```C
// int (*const operations[4])(int, int) = {
//         &sum,
//         &subtraction,
//         &product,
//         &division
// };
// ```
//
// Podemos omitir a indicação explícita do número de itens do _array_, deixando
// ao compilador o trabalho de calcular o número de itens a partir do número de
// itens no inicializador:
//
// ```C
// int (*const operations[])(int, int) = {
//         &sum,
//         &subtraction,
//         &product,
//         &division
// };
// ```
//
// Finalmente, tirando partido do facto de, salvo raras excepções, o C converter
// qualquer referência ao nome de um rotina num ponteiro para essa mesma rotina,
// podemos simplificar a definição anterior para a nossa versão definitiva:
//
// ```C
// int (*const operations[])(int, int) = {
//         sum,
//         subtraction,
//         product,
//         division
// };
// ```
int (*const operations[])(int, int) = {
	sum,
	subtraction,
	product,
	division
};

// Usamos agora o truque usual para obter o número de itens de um _array_:
// dividir o espaço de memória total ocupado pelo _array_ pelo espaço ocupado
// por cada um dos seus itens. Para isso usamos o operador `sizeof`.
const int number_of_operations =
	sizeof(operations) /
	sizeof(operations[0]);

// Definimos a rotina principal, onde experimentamos o conceito de _array_ de
// rotinas.
int main(void)
{
	// Percorremos cada um dos itens do _array_ `operations`.
	for (int i = 0; i != number_of_operations; i++)
		// Invocamos com os argumentos 5 e 2 a função apontada por cada
		// item do _array_. O resultado será, naturalmente:
		//
		// ```
		// Operation 0: 7
		// Operation 1: 3
		// Operation 2: 10
		// Operation 3: 2
		// ```
		//
		// Note que, para invocar a função apontada pelo item `i` do
		// _array_ `operations`, poderia parecer obrigatório usar o
		// operador `*`:
		//
		// ```C
		// printf("Operation %d: %d\n", i,
		//         (*operations[i])(5, 2));
		// ```
		//
		// A linguagem C, no entanto, permite-nos omitir o operador `*`
		// e aplicar directamente o operador de invocação `()` ao
		// ponteiro para a função. Daí que o código apresentado seja
		//
		// ```C
		// printf("Operation %d: %d\n", i,
		//         operations[i](5, 2));

		// ```
		printf("Operation %d: %d\n", i,
			operations[i](5, 2));

	// Terminamos assinalando sucesso.
	return EXIT_SUCCESS;
}
