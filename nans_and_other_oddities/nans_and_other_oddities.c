// NaN e outros que tais
// =====================
//
// Embora a norma da linguagem C não obrigue a isso, a maior parte das suas
// implementações conformam-se com a norma [IEC
// 60559:1989](http://en.wikipedia.org/wiki/IEEE_754-1985) (antes conhecida por
// IEC 559:1989 e por ANSI/IEEE 754-1985; esta norma tem uma versão mais
// recente, a [ISO/IEC/IEEE
// 60559:2011](http://en.wikipedia.org/wiki/IEEE_floating_point), cuja
// designação original é IEEE 754-2008). Estas normas especificam a
// representação e o comportamento dos números de vírgula flutuante.
//
// Vírgula flutuante: fujam!
// -------------------------
//
// A mensagem é simples: sempre que possível, e a não ser que se tenha estudado
// bem o assunto, _deve-se evitar usar valores_ de vírgula flutuante nos
// programas_. É que a computação numérica é uma disciplina difícil e cheia de
// armadilhas. A programação básica e a algoritmia são desafio suficiente,
// neste momento. Logo que possa, no entanto, tente obter uma boa formação em
// computação ou métodos numéricos. Verá que vale a pena.
//
// Valores especiais
// -----------------
//
// A norma IEC 60559:1989, quando implementada pelos compiladores de C, o que
// normalmente acontece, estende a gama dos números representados de modo a
// incluir alguns valores especiais:
//
// - Para além do 0, o -0. Curiosamente, embora um e outro produzam resultados
//   diferentes quando usados como divisores, são considerados como iguais.
// - Os valores -∞ e +∞.
// - Um valor especial, conhecido como _not-a-number_, ou NaN, que representa...
// algo que não é um número. Por exemplo, o resultado de uma indeterminação.

// Inclusões
// ---------
//
// As inclusões usuais de ficheiros de cabeçalho, para poder usar as rotinas de
// escrita no ecrã e para poder devolver `EXIT_SUCCESS`.
#include <stdio.h>
#include <stdlib.h>

// Esta inclusão permite usar `true` e `false` no código, tornando-o mais
// legível.
#include <stdbool.h>

// Macros
// ------
//
// Definição de duas macros destinadas a simplificar a escrita de código para
// mostrar no ecrã uma expressão e o seu resoldado.
#define print(double_value) printf(#double_value " = %g\n", (double_value))
#define print_boolean(boolean) \
	printf(#boolean " is %s\n", (boolean) ? "true" : "false")

// Experiências
// ------------
int main()
{
	// A divisão _inteira_ por zero resulta num erro fatal durante a
	// execução do programa. A divisão inteira não está abrangida pela norma
	// que se referiu mais acima. Os números inteiros, tal como
	// representados em C, não suportam valores infinitos.
	if (false) {
		// O programa abortaria se atingisse esta linha!
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

	// !!!!!no literals for infinity NaN. !!!!Check constants and macros
	double plus_infinity = 1.0 / 0.0;
	double minus_infinity = 1.0 / -0.0;
	double not_a_number = 0.0 / 0.0;

	// !!!!Operações com infinito têm comportamento esperado.
	//
	// ```
	// plus_infinity = inf
	// minus_infinity = -inf
	// 1.0 / plus_infinity = 0
	// 1.0 / minus_infinity = -0
	// plus_infinity + minus_infinity = nan
	// plus_infinity / minus_infinity = nan
	// ```
	print(plus_infinity);
	print(minus_infinity);
	print(1.0 / plus_infinity);
	print(1.0 / minus_infinity);
	print(plus_infinity + minus_infinity);
	print(plus_infinity / minus_infinity);

	// !!!Alguns casos curiosos.
	//
	// ```
	// 0.0 == -0.0 is true
	// 0.0 != -0.0 is false
	// plus_infinity == minus_infinity is false
	// not_a_number == not_a_number is false
	// not_a_number != not_a_number is true
	// ```
	print_boolean(0.0 == -0.0);
	print_boolean(0.0 != -0.0);
	print_boolean(plus_infinity == minus_infinity);
	print_boolean(not_a_number == not_a_number);
	print_boolean(not_a_number != not_a_number);

	return EXIT_SUCCESS;
}
