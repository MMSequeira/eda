// `nans_and_other_oddities.c` &ndash; NaN e outros que tais
// =========================================================
//
// Embora a norma da linguagem C não obrigue a isso, a maior parte das suas
// implementações conformam-se com a norma [IEC
// 60559:1989](http://en.wikipedia.org/wiki/IEEE_754-1985) (antes conhecida por
// IEC 559:1989 e por ANSI/IEEE 754-1985; esta norma tem uma versão mais
// recente, a [ISO/IEC/IEEE
// 60559:2011](http://en.wikipedia.org/wiki/IEEE_floating_point), cuja
// designação original é IEEE 754-2008). Estas normas especificam a
// representação e o comportamento dos números de [vírgula
// flutuante](http://en.wikipedia.org/wiki/Floating_point).
//
// Vírgula flutuante: fujam!
// -------------------------
//
// A mensagem é simples: sempre que possível, e a não ser que tenha estudado bem
// o assunto, _deve evitar usar valores_ de vírgula flutuante nos seus
// programas_. A computação numérica é uma disciplina difícil e cheia de
// armadilhas. A programação básica e a algoritmia são desafio suficiente, neste
// momento. Logo que possa, no entanto, tente obter uma boa formação em
// [computação numérica](http://en.wikipedia.org/wiki/Numerical_analysis) (ou
// «análise numérica», ou ainda em «métodos numéricos», como a área de estudo
// também é conhecida). Verá que vale a pena.
//
// Valores especiais
// -----------------
//
// A norma IEC 60559:1989, quando implementada pelos compiladores de C, o que
// normalmente acontece, estende a gama dos números representados de modo a
// incluir alguns valores especiais:
//
// - Para além do 0 (zero), o -0 (zero negativo). Curiosamente, embora um e
//   outro produzam resultados diferentes quando usados como divisores, são
//   considerados como iguais pela linguagem, segundo o operador `==`.
// - Os valores -∞ e +∞.
// - Um valor especial, conhecido como _not-a-number_, ou NaN, que representa...
// algo que não é um número. Por exemplo, um resultado indeterminado.

// Inclusões
// ---------
//
// As inclusões usuais de ficheiros de cabeçalho, para poder usar o procedimento
// `printf` de escrita no ecrã e para poder devolver `EXIT_SUCCESS` no final do
// programa.
#include <stdio.h>
#include <stdlib.h>

// Esta inclusão permite usar `true` e `false` no código, tornando-o mais
// legível.
#include <stdbool.h>

// Macros
// ------
//
// Definição de duas macros destinadas a simplificar a escrita de código para
// mostrar no ecrã uma expressão e o seu resultado.
#define print(double_value) printf(#double_value " = %g\n", (double_value))
#define print_boolean(boolean_value) \
	printf(#boolean_value " is %s\n", (boolean_value) ? "true" : "false")

// Notas
// -----
//
// Todos os exemplos abaixo usam o tipo `double`, de entre os três tipos de
// vírgula flutuante do C. De facto, uma prática usual na programação em C é
// justamente a de, salvo quando existe alguma boa razão em contrário, usar o
// tipo `double`, e não `float` ou `long double`.
//
// Experiências
// ------------
int main()
{
	// A divisão _inteira_ por zero resulta num erro fatal durante a
	// execução do programa. A divisão inteira não está abrangida pela norma
	// que se referiu mais acima. Os números inteiros, tal como
	// representados em C, não suportam valores infinitos. O programa
	// abortaria se atingisse a instrução com a divisão por zero.
	if (false) {
		int n = 1 / 0;
	}

	// As divisões por zero são suportadas directamente quando se trata de
	// valores de vírgula flutuante. O único caso especial diz respeito à
	// divisão de zero por zero. Em consonância com a nossa intuição de que
	// o resultado é indeterminado, o resultado é o valor especial NaN:
	//
	// ```
	// 1.0 / 0.0 = inf
	// 1.0 / +0.0 = inf
	// 1.0 / -0.0 = -inf
	// 0.0 / 0.0 = nan
	// ```
	print(1.0 / 0.0);
	print(1.0 / +0.0);
	print(1.0 / -0.0);
	print(0.0 / 0.0);

	// Em C não é possível usar `inf`, `-inf` ou `NaN` como [valores
	// literais](http://en.wikipedia.org/wiki/Literal_(computer_programming)
	// ), i.e., escritos tal e qual no nosso código. Se incluirmos o
	// ficheiro de cabeçalho `math.h`, ficamos com algumas macros definidas
	// que permitem ultrapassar esse problema (e.g., `HUGE_VAL`, do tipo
	// `double`, `INFINITY`, do tipo `float`, e `NAN`, também do tipo
	// `float`), se bem que de forma muito pouco consistente. Nada nos
	// impede, no entanto, de criarmos as nossas próprias constantes.
	const double infinity = 1.0 / 0.0;
	const double plus_infinity = infinity;
	const double minus_infinity = 1.0 / -0.0;
	const double nan = 0.0 / 0.0;
	const double not_a_number = nan;

	// As constantes definidas têm os valores pretendidos, pelo menos nos ambientes em que a norma IEC 60559 está implementada.
	//
	// ```
	// plus_infinity = inf
	// minus_infinity = -inf
	// not_a_number = nan
	// ```
	print(plus_infinity);
	print(minus_infinity);
	print(not_a_number);

	// Mais alguns exemplos de operação com os valores especiais que
	// resultam naquilo que esperaríamos.
	//
	// ```
	// 1.0 / plus_infinity = 0
	// 1.0 / minus_infinity = -0
	// plus_infinity + minus_infinity = nan
	// plus_infinity / minus_infinity = nan
	// plus_infinity == minus_infinity is false
	// ```
	print(1.0 / plus_infinity);
	print(1.0 / minus_infinity);
	print(plus_infinity + minus_infinity);
	print(plus_infinity / minus_infinity);
	print_boolean(plus_infinity == minus_infinity);

	// Finalmente, alguns factos importantes:
	//
	// - Os valores `0.0` e `-0.0` são considerados iguais, apesar de darem
	//   origem a resultados simátricos quando usados como divisor de um
	//   qualquer número.
	//
	// - Em quase todas as operações do C, o valor NaN funciona como uma
	//   espécie de elemento absorvente: onde surge, o resultado é
	//   também NaN.
	//
	// - Há casos em que o carácter de elemento absorvente não se aplica.
	//   Por exemplo, no caso dos operadores relacionais com os quais o
	//   resultado é sempre falso, ou no caso dos operadores de comparação,
	//   cujo comportamento é realmente estranho:
	//
	// - Se algum os operandos de uma comparação com o operador `==` é NaN,
	//   então o resultado é falso, como seria (?) de esperar, mesmo se
	//   ambos operadores são NaN, o que talvez já não fosse de esperar. O
	//   caso do operador `!=` é o inverso do do operador `==`, resultando
	//   sempre em verdadeiro, mesmo quando ambos os operandos são NaN. 
	//
	// ```
	// 0.0 > -0.0 is false
	// 0.0 == -0.0 is true
	// 0.0 != -0.0 is false
	// not_a_number > 1.0 is false
	// not_a_number < 1.0 is false
	// not_a_number >= 1.0 is false
	// not_a_number <= 1.0 is false
	// not_a_number > not_a_number is false
	// not_a_number < not_a_number is false
	// not_a_number >= not_a_number is false
	// not_a_number <= not_a_number is false
	// not_a_number == 1.0 is false
	// not_a_number != 1.0 is true
	// not_a_number == not_a_number is false
	// not_a_number != not_a_number is true
	// ```
	//
	// O comportamento estranho dos operadores `==` e `!=` quando ambos os
	// operandos são NaN pode ser usado para verificar se um valor é NaN (se
	// bem que exista já um predicado para isso mesmo declarado em `math.h`,
	// viz. `isnan()`):
	//
	// ```C
	// bool is_nan(double value)
	// {
	//         return value != value;
	// }
	// ```

	print_boolean(0.0 > -0.0);
	print_boolean(0.0 == -0.0);
	print_boolean(0.0 != -0.0);
	print_boolean(not_a_number > 1.0);
	print_boolean(not_a_number < 1.0);
	print_boolean(not_a_number >= 1.0);
	print_boolean(not_a_number <= 1.0);
	print_boolean(not_a_number > not_a_number);
	print_boolean(not_a_number < not_a_number);
	print_boolean(not_a_number >= not_a_number);
	print_boolean(not_a_number <= not_a_number);
	print_boolean(not_a_number == 1.0);
	print_boolean(not_a_number != 1.0);
	print_boolean(not_a_number == not_a_number);
	print_boolean(not_a_number != not_a_number);

	return EXIT_SUCCESS;
}
