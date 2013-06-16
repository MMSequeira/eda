// `hello_world_correct.c` &ndash; Versão correcta do `hello_world.c`
// ==================================================================
//
// Este programa é a versão corrigida do código em
// [`hello_world.c`](hello_world.c.html)).

// Inclusão de ficheiros de cabeçalho
// ----------------------------------
//
// Incluímos quatro dos ficheiros de cabeçalho da biblioteca padrão do C, i.e.,
// da biblioteca que acompanha a linguagem C tal como definida pela sua norma:
//
// - `stdio.h` &ndash; Declara os procedimentos `printf()` e `scanf()`, usados
// respectivamente para escrever no ecrã (ou melhor, no canal de saída) e
// para ler do teclado (ou melhor, do canal de entrada). Declara também
// `feof()`, `ferror()`, `fprintf()` e `stderr`.
//
// - `stdlib.h` &ndash; Define a _macro_ `EXIT_SUCCESS`, que é usada para
// assinalar sucesso na execução de um programa, quando este termina, ou
// seja, quando se _sai_ do programa, e a macro `EXIT_FAILURE`, que é usada da
// mesma forma, mas para assinalar insucesso.
//
// - `stdbool.h` &ndash; Para podermos usar o valor booleano `true` como 
// _guarda_ do ciclo `while`.
//
// - `assert.h` &ndash; Para podermos usar a rotina `assert()` para verificar a
// validade dos argumentos passados à função `factorial()`.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Definição da função `factorial()`
// ---------------------------------
//
int factorial(const int n)
{
	// Verificamos a validade do argumento recebido usando a rotina especial
	// (na realidade uma _macro_ do pré-processador) chamada `assert()`. O
	// limite superior para o valor do argumento é muito baixo: 12. Isso
	// deve-se a dois factos:
	//
	// 1. Os `int` em C, nos nossos ambientes típicos, são guardados em
	// apenas 32 bit interpretados em complemento para dois, pelo que um
	// inteiro só pode tomar valores entre ![-2^31](http://bit.ly/16CVI6B) e
	// ![2^31-1](http://bit.ly/12AavZ0), ou seja, entre
	// -2&thinsp;147&thinsp;483&thinsp;648 e
	// 2&thinsp;147&thinsp;483&thinsp;647.
	//
	// 2. O factorial é uma função de crescimento muito rápido, pelo que
	// 13!, com o valor 6&thinsp;227&thinsp;020&thinsp;800, excede já o
	// limite superior dos `int`.
	assert(0 <= n && n <= 12);

	// Começamos por verificar se se aplica o caso especial em que o valor
	// de `n` é zero.
	if (n == 0)
	// Se se aplicar, retornamos imediatamente (i.e., terminamos a função,
	// retornando ao ponto de invocação) _devolvendo_ o valor 1.
		return 1;

	// No caso contrário, retornamos devolvendo o produto entre o valor de
	// `n` e o valor devolvido por uma nova invocação da mesma função,
	// embora com um valor mais pequeno passado como argumento, ou seja, _n
	// - 1_ em vez de _n_. Trata-se de uma invocação recursiva da própria
	// função.
	return n * factorial(n - 1);
}

// A rotina principal `main()`
// ---------------------------
//
int main(void)
{
	// Começamos por escrever no ecrã o nome e o propósito do programa.
	printf("Hello world! Let's calculate the factorial of a number.\n");

	// Uma vez que o objectivo do programa é calcular o factorial de um
	// número, usamos este ciclo para obter do utilizado um número inteiro
	// não negativo, que ficará guardado na variável `number`.
	int number;
	// Usamos um ciclo «infinito», pois o local apropriado para a
	// verificação da guarda não é nem no início do passo, nem no seu final,
	// mas sim a meio. (Na realidade o ciclo tem duas saídas: uma se a
	// leitura tiver sucesso, outra, terminando o programa, se durante a
	// leitura ocorrer um erro irrecuperável.)
	while(true) {
		// Pedimos ao utilizador para introduzir um número inteiro não
		// negativo. Neste caso não terminamos a linha, pois pretendemos
		// que a resposta do utilizador surja visualmente à frente do
		// texto que escrevemos. Em vez disso, escrevemos um espaço,
		// para que o número introduzido pelo utilizador não surja
		// «colado» ao nosso texto. A leitura dos caracteres
		// introduzidos pelo utilizador só é realizada depois de este
		// carregar em «enter», o que terá o efeito visual de terminar
		// esta linha.
		printf("Please enter a non-negative integer "
		       "between 0 and 12: ");

		// Tentamos ler a resposta do utilizador com um número inteiro.
		// Se a leitura tiver sucesso e o número estiver dentro da gama
		// pretendida, interrompemos o ciclo. A função `scanf()` devolve
		// o número de atribuições a itens de entrada realizadas com
		// sucesso. No nosso caso podemos saber se foi lido um valor
		// inteiro com sucesso verificando se o valor devolvido foi 1.
		// Para saber se o valor lido é válido, verificamos se se
		// encontra entre 0 e 12. Caso tudo tenha corrido bem, o ciclo é
		// interrompido através da instrução `break`.
		if (scanf("%d", &number) == 1 && 0 <= number && number <= 12)
			break;

		// Neste ponto sabemos que algum erro ocorreu. Temos de
		// verificar se esse erro é irrecuperável, o que acontece se o
		// canal de leitura `stdin` tiver ficado marcado como tendo sido
		// atingido o fim do ficheiro (a entrada de um programa pode ser
		// redireccionada de modo a ser feita a partir de um ficheiro)
		// ou como tendo ocorrido um outro erro de leitura.
		if (feof(stdin) || ferror(stdin)) {
			// Se ocorreu um erro irrecuperável, assinalamo-lo no
			// canal apropriado para o efeito, `stderr`, e
			// terminamos o programa devolvendo um código de erro.
			fprintf(stderr,
				"Unrecoverable error reading user response. "
				"Exiting.\n");

			// Terminamos o programa devolvendo o valor especial
			// `EXIT_FAILURE` para comunicar este erro à entidade
			// que executou o programa.
			return EXIT_FAILURE;
		}

		// Neste ponto sabemos que a leitura não teve sucesso, mas que
		// isso não se deveu a um erro irrecuperável. O erro pode ter
		// ocorrido por o utilizador não ter introduzido um número
		// inteiro ou por ter introduzido um valor inteiro com um valor
		// fora da gama válida. Assim, começamos por alertar o
		// utilizador acerca do seu erro.
		printf("Invalid response. Try again.\n");

		// Depois, limpamos o canal de entrada de tudo o que o
		// utilizador tiver introduzido até ao final da linha, de modo a
		// que este possa tentar introduzir um novo valor. Para
		// descartar uma linha completa de caracteres, invocamos o
		// procedimento `scanf()` com a cadeia de formação
		// `%*[^\n]%*1[\n]`. O significado é o seguinte:
		//
		// - Primeira especificação de conversão, `%*[^\n]`: Ler _e
		//   descartar_ (daí o caractere `*`) todos os caracteres até o
		//   próximo fim-de-linha, exclusive.
		//
		// - Segunda especificação de conversão, `%*1[\n]`: Ler _e
		//   descartar_ (daí o caractere `*`) exactamente um caractere
		//   fim-de-linha. Colocar `\n` na cadeia de formatação em vez
		//   desta especificação de conversão não teria o resultado
		//   pretendido, pois o procedimento `scanf()` interpreta todos
		//   os caracteres «brancos» como uma ordem para ignorar um
		//   número arbitrário de caracteres brancos até ser encontrado
		//   o primeiro caractere não branco, o que levaria a que não
		//   surgisse novo pedido de inserção de um número válido
		//   enquanto o utilizador fosse carregando em «enter».
		scanf("%*[^\n]%*1[\n]");
	}

	// Finalmente, podemos calcular o factorial pretendido e escrever o
	// resultado no ecrã. Para isso invocamos o procedimento `printf()`
	// passando-lhe três argumentos.
	//
	// O primeiro argumento, `"%d! = %d\n"`, é uma cadeia de caracteres de
	// formação. Esta cadeia da caracteres é interpretada pelo procedimento
	// `printf()`, que imprime directamente no ecrã os caracteres da cadeia
	// de formação, excepto quando encontra _especificações de formatação_
	// que, tal como no caso do procedimento `scanf()`, são introduzidas
	// pelo caractere `%`. Neste caso temos duas especificações de
	// formatação, ambas `%d`.
	//
	// Quando o procedimento `printf()` encontra a primeira especificação de
	// formatação, transforma o valor do segundo argumento, que tem de ser
	// um `int`, uma vez que após o caractere `%` se encontra o caractere
	// `d`, numa sequência de caracteres e escreve-os no ecrã. Isso leva a
	// que o valor da variável `number` seja escrito no ecrã, na notação
	// decimal usual. Quando o procedimento `printf()` encontra a segunda
	// especificação de formatação, transforma o valor do terceiro argumento
	// numa sequência de caracteres e escreve-os no ecrã. Isso leva a que o
	// valor devolvido pela função `factorial()` quando invocada com o
	// argumento `number` seja escrito no ecrã, na notação decimal usual.
	//
	// Por exemplo, admitindo que o valor de `number` é 5, então esta
	// instrução escreve no ecrã a seguinte linha:
	//
	// ```
	// 5! = 120
	// ```
	printf("%d! = %d\n", number, factorial(number));

	// Terminada a impressão do factorial calculado, podemos terminar o
	// programa retornando da execução da rotina `main()`. Uma vez que a
	// execução teve sucesso, devolvemos o valor especial `EXIT_SUCCESS` ao
	// retornar.
	return EXIT_SUCCESS;
}
