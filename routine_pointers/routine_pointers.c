// Ponteiros para rotinas
// ======================
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
// código que se segue, usaremos um pouco de «magia» do pré-processador.

// Se quisermos activar a versão explícita do código, comentamos esta
// definição de macro.
#define CLEAN_VERSION

// Esta directiva do pré-processador do C selecciona o troço de código a
// compilar, consoante esteja ou não definida a macro `CLEAN_VERSION`.
#ifdef CLEAN_VERSION

// Versão mais «limpa» e menos explícita do código
// -----------------------------------------------
//
// !!!!!!!!

void try_function(int f(int), int value)
{
	printf("f(%d) = %d\n", value, f(value));
}

int main()
{
	try_function(double_of, 4); // => f(4) = 8
	try_function(triple_of, 4); // => f(4) = 12

	// Neste caso ..........
	//
	// Note-se que !!!!!!!!!!
	//
	// ```C
	// int f(int) = double_of; ERROR!
	// ```
	int (*f)(int) = double_of;
	
	printf("f(5) = %d\n", f(5)); // => f(5) = 10

	return EXIT_SUCCESS;
}

#else

// Versão menos «limpa» e mais explícita do código
// -----------------------------------------------
//
// !!!!!!!!

void try_function(int (*f)(int), int value)
{
	printf("f(%d) = %d\n", value, (*f)(value));
}

int main()
{
	try_function(&double_of, 4); // => f(4) = 8
	try_function(&triple_of, 4); // => f(4) = 12

	int (*f)(int) = &double_of;

	printf("f(5) = %d\n", (*f)(5)); // => f(5) = 10

	return EXIT_SUCCESS;
}

#endif // CLEAN_VERSION