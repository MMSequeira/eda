// `routine_pointers.c` &ndash; Ponteiros para rotinas
// ===================================================
//
// Um dos mecanismos que mais flexibilidade confere a uma linguagem de
// programação é a possibilidade de parametrizar módulos (e.g., rotinas ou, nas
// linguagens orientadas por objectos, classes ou objectos) com mecanismos. Ou
// seja, a possibilidade de deixar em aberto, durante a criação desses módulos,
// algumas das rotinas a que o módulo recorrerá. A indicação dessas rotinas é
// deixada a cargo do código cliente, i.e., do código que parametriza e usa
// esses módulos. Em C, o mecanismo que suporta este tipo de prática é o dos
// [ponteiros para rotinas](http://en.wikipedia.org/wiki/Function_pointer).
//
// Este programa exemplifica a utilização de ponteiros para rotinas em C,
// demonstrando duas formas de utilização em tudo equivalente. Uma dessas
// versões é mais «limpa», embora menos explícita. A outra é mais «suja» (no
// sentido em que o código é mais denso e difícil de ler), embora totalmente
// explícita. Em ambos os casos, o objectivo é parametrizar um procedimento de
// teste, passando-lhe como argumento uma de duas funções a testar. O programa
// exemplifica também a utilização de variáveis para guardar ponteiros para
// rotinas.

// Inclusões
// ---------
//
// As inclusões usuais para poder usar o procedimento `printf` para poder
// devolver `EXIT_SUCCESS` no final do programa.
#include <stdio.h>
#include <stdlib.h>

// Duas funções
// ------------
//
// Estas duas funções serão usadas no código que se segue. São absolutamente
// triviais, devolvendo respectivamente o dobro e o triplo do valor inteiro
// recebido como argumento.
int double_of(int n)
{
	return 2 * n;
}

int triple_of(int n)
{
	return 3 * n;
}

// Magia do pré-processador
// ------------------------
//
// Para podermos ter duas versões absolutamente equivalentes e lado a lado do
// código que se segue, usaremos um pouco de «magia» do pré-processador. Se
// quisermos activar a versão explícita do código, comentamos esta definição de
// macro.
#define CLEAN_VERSION

// Esta directiva do pré-processador do C selecciona o troço de código a
// compilar, consoante esteja ou não definida a macro `CLEAN_VERSION`.
#ifdef CLEAN_VERSION

// Versão mais «limpa» e menos explícita do código
// -----------------------------------------------
//
// ### O procedimento `try_function()`
//
// O procedimento `try_function()` é um módulo (as rotinas são módulos)
// parametrizável por uma função. Essa função é recebida como argumento, sendo
// conhecida internamente ao procedimento por `f`. Note-se que o tipo de `f` é
// `int f(int)` (ver mais abaixo porque é que esta descrição do tipo de `f` está
// errada, na realidade), ou seja, uma função que recebe um inteiro como
// argumento e devolve um inteiro ao retornar. Este tipo é compatível com as
// definições das funções `double_of()` e `triple_of()`, que por isso podem ser
// passadas como argumento a este procedimento, como de resto acontece mais
// abaixo, no procedimento `main()`. O segundo parâmetro do procedimento
// `try_function()` guarda o valor a passar como argumento à função recebida
// como primeiro argumento quando esta for invocada.
void try_function(int f(int), int value)
{
	// A invocação da função passada como argumento faz-se da forma usual,
	// embora através de `f`. Recorde-se que `f` tanto pode ser a função
	// `double_of` como a função `triple_pf`. Aliás, pode ser qualquer
	// função com apenas um parâmetro `int` e que, ao terminar, devolva
	// também um `int`. Neste local não precisamos de saber que função é:
	// limitamo-nos a invocá-la.
	printf("f(%d) = %d\n", value, f(value));
}

//
int main()
{
	// ### Invocação do procedimento definido
	//
	// Invocamos o procedimento `try_function()` definido acima, passando-
	// lhe como primeiro argumento a função `double_of` e, depois, a função
	// `triple_of`. Em ambos os casos o segundo argumento tem o valor 4. Os
	// valores impressos no ecrã são, como seria de esperar, 8 e 12, ou
	// seja, o dobro e o triplo de 4, respectivamente.
	try_function(double_of, 4); // => f(4) = 8
	try_function(triple_of, 4); // => f(4) = 12

	// ### Variáveis locais (apontando) rotinas
	//
	// Da mesma forma que podemos passar rotinas como argumento a outras
	// rotinas, podemos guardar rotinas em variáveis. OK, OK. É falso. Não
	// podemos. Temos vindo a descrever as coisas de forma simplista. Mas
	// pelo menos avisámos! E neste ponto, já não nos podemos iludir mais: o
	// que se pode guardar em variáveis são _ponteiros_ para rotinas. A
	// linguagem C é que é simpática e nos poupa ao trabalho de indicar qual
	// o verdadeiro tipo de uma rotina recebida como argumento. Tal como no
	// caso dos _arrays_, o C transforma uma declaração de um rotina como
	// parâmetro numa declaração de um _ponteiro_ para uma rotina. Mais
	// sobre o assunto mais abaixo, na versão menos «limpa do código». Mas
	// não o faz quando se trata de definir uma variável local. É por isso
	// que a linha de código
	//
	// ```C
	// int f(int) = double_of;
	// ```
	//
	// produz um erro de compilação. Sem a indicação explícita de que se
	// trata de um ponteiro, o C assume tratar-se da declaração (da
	// existência algures) de uma função `f()`. O problema resolve-se
	// indicando explicitamente que a variável `f` é um ponteiro para uma
	// função. Note-se que o asterisco antes do nome da variável reflecte a
	// forma como a variável será utilizada. Aliás, as declarações em C
	// seguem esse padrão: indicar a forma de utilização da variável e
	// indicar o tipo que resulta dessa utilização. Os parênteses em torno
	// de `*f` devem-se ao facto de o operador de invocação de rotinas (os
	// parênteses que se seguem ao nome da rotina e que envolvem os
	// argumentos a passar a essa rotina) ter uma precedência superior à do
	// operador de desreferenciação. Assim, `int *f(int)` seria interpretado
	// como a declaração de existência algures de uma função `f()`,
	// invocável com um único valor inteiro, e devolvendo, quando retorna,
	// um _ponteiro_ para um valor inteiro.
	int (*f)(int) = double_of;
	
	// Naturalmente, o resultado será a impressão no ecrã do dobro de cinco.
	// Repare-se na forma simples de invocação.
	printf("f(5) = %d\n", f(5)); // => f(5) = 10

	//
	return EXIT_SUCCESS;
}

#else

// A versão a cima é limpa e fácil de perceber. Mas esconde muito sob essa
// aparência de simplicidade. Vejamos exactamente o quê.

// Versão menos «limpa» e mais explícita do código
// -----------------------------------------------
//
// ### O procedimento `try_function()`
//
// O procedimento `try_function()` é um módulo (as rotinas são módulos)
// parametrizável por um ponteiro para uma função. Esse ponteiro para uma função
// é recebido como argumento, sendo conhecido internamente ao procedimento por
// `f`. Note-se que o tipo de `f` é `int (*f)(int)`, ou seja, um ponteiro para
// uma função que recebe um inteiro como argumento e devolve um inteiro ao
// retornar. O tipo deste ponteiro é compatível com as definições das funções
// `double_of()` e `triple_of()`, cujos endereços por isso podem ser passados
// como argumento a este procedimento, como de resto acontece mais abaixo, no
// procedimento `main()`. O segundo parâmetro do procedimento `try_function()`
// guarda o valor a passar como argumento à função recebida como primeiro
// argumento quando esta for invocada.
void try_function(int (*f)(int), int value)
{
	// A invocação da função cujo endereço foi passado como argumento faz-se
	// da forma usual, embora através de `f`. Recorde-se que `f` tanto pode
	// apontar para a função `double_of` como para a função `triple_pf`.
	// Aliás, pode apontar para qualquer função com apenas um parâmetro
	// `int` e que, ao terminar, devolva também um `int`. Neste local não
	// precisamos de saber que função é: limitamo-nos a invocá-la. A
	// invocação é feita depois de desreferenciar o ponteiro usando o
	// operador `*`.
	printf("(*f)(%d) = %d\n", value, (*f)(value));
}

//
int main()
{
	// ### Invocação do procedimento definido
	//
	// Invocamos o procedimento `try_function()` definido acima, passando-
	// lhe como primeiro argumento um ponteiro para a função `double_of` e,
	// depois, um ponteiro para a função `triple_of`. Em ambos os casos o
	// segundo argumento tem o valor 4. Note-se que se usa o operador
	// endereço, ou seja, o operador `&` para obter os ponteiros a passar
	// como argumento ao procedimento invocado. Os valores impressos no ecrã
	// são, como seria de esperar, 8 e 12, ou seja, o dobro e o triplo de 4,
	// respectivamente.
	try_function(&double_of, 4); // => (*f)(4) = 8
	try_function(&triple_of, 4); // => (*f)(4) = 12

	// ### Variáveis locais (apontando) rotinas
	//
	// Da mesma forma que podemos passar ponteiros para rotinas como argumento a outras
	// rotinas, podemos guardar ponteiros para rotinas em variáveis. Os parênteses em torno
	// de `*f` devem-se ao facto de o operador de invocação de rotinas (os
	// parênteses que se seguem ao nome da rotina e que envolvem os
	// argumentos a passar a essa rotina) ter uma precedência superior à do
	// operador de desreferenciação.
	int (*f)(int) = &double_of;

	// A invocação da função apontada por `f` é feita da forma usual, embora
	// apenas depois de desreferenciar o ponteiro usando o operador
	// conteúdo, ou seja, o operador `*`.
	printf("(*f)(5) = %d\n", (*f)(5)); // => (*f)(5) = 10

	//
	return EXIT_SUCCESS;
}

#endif // CLEAN_VERSION

// As regras
// ---------
//
// De forma resumida, as regras usadas pela linguagem C no que respeita a
// ponteiros para rotinas são as seguintes:
//
// - Sempre que um parâmetro for declarado como sendo uma rotina, o compilador
//   interpreta-a como declarando um _ponteiro_ para rotinas do tipo indicado.
//   Ou seja, o compilador transforma declarações de parâmetros da
//   forma<code>_tipo_ _nome_(_tipos_dos_parânetros_)</code> em declarações da
//   forma <code>_tipo_ (*_nome_)(_tipos_dos_parânetros_)</code>.
//
// - Quando o nome de uma rotina surge numa expressão (que não como operando do
//   operador de invocação), o compilador interpreta-o como sendo um ponteiro
//   para essa rotina. Ou seja, salva a excepção já referida, e se estiver
//   declarada uma rotina com nome `rotina`, então `rotina` e `&rotina` são
//   expressões equivalentes.
//
// - Podemos invocar uma rotina através de um seu ponteiro, e.g.,
//   <code>_ponteiro_para_rotina_</code>, de duas formas totalmente
//   equivalentes: (a) explicitando o carácter de ponteiro do ponteiro,
//   desreferenciando-o explicitamente antes de proceder à invocação, i.e.,
//   <code>(*_ponteiro_para_rotina_)(_lista_de_argumentos_)</code>, ou (b)
//   procedendo à invocação como se se tratasse de uma rotina, e não de um
//   ponteiro para ela, i.e.,
//   <code>_ponteiro_para_rotina_(_lista_de_argumentos_)</code>.
//
// Devemos usar estas regras sempre com o objectivo de tornar o código mais
// claro, pelo que tendemos a preferir as versões mais sintéticas e que menos
// explicitam a natureza de ponteiro dos ponteiros para rotinas.
//
// Magia, mesmo?
// -------------
//
// O pré-processador é mesmo mágico, não é? Pois. É. Demasiado. Evite recorrer a
// ele. Use-o apenas onde indispensável (e.g., inclusões de ficheiros de
// cabeçalho, evitando as consequências da inclusão múltipla, etc.). O exemplo
// de compilação condicional que aqui apresentamos encaixa-se perfeitamente no
// conjunto de práticas a evitar sempre que possível. Usámo-lo apenas para
// podermos manter num único ficheiro duas versões equivalentes, embora
// diferentes, do mesmo código, pois isso traz evidentes vantagens pedagógicas.
// Cremos que essas vantagens são suficientes para justificar a violação de uma
// boa prática.
