// `hello_world.c` &ndash; Estrutura de um programa em C
// =====================================================
//
// Este programa ilustra a estrutura básica de um programa escrito na linguagem
// C. O objectivo deste programa é imprimir no ecrã o factorial de um número
// inteiro introduzido pelo utilizador do programa.
//
// Avisos!
// -------
//
// De modo a mantê-lo curto, optámos por omitir deste programa todo o código de
// verificação de erros do utilizador. _Todos os programas têm de saber lidar
// com erros dos seus utilizadores!_  Não o fazer é um erro _grave_. Este
// programa está, assim, _gravemente errado_. Não diga que não o avisámos. :-)
//
// Ficheiro e nome
// ---------------
//
// Este programa consiste numa única _unidade de compilação_. Ou seja,
// corresponde a um único ficheiro destinado a ser _compilado_. Os ficheiros em
// linguagem C que se destinam a ser compilados possuem convencionalmente a
// extensão `.c`. O nome do ficheiro é, assim, `hello_world.c`.
//
// Este ficheiro não é suficiente para _construir_ o ficheiro executável, pois
// recorre a ferramentas da _biblioteca padrão_ do C. Em particular, recorre a
// rotinas de leitura e escrita de dados e recorre à _macro_ `EXIT_SUCCESS`.
//
// A construção do executável
// --------------------------
//
// Os passos usuais na construção de um ficheiro executável a partir de um
// programa em linguagem C são os seguintes:
//
// 1. Pré-processar cada um dos ficheiros `.c` - O pré-processador é um programa
// que lê um ficheiro contendo código C e directivas de pré-processamento e
// interpreta estas directivas, produzindo um ficheiro contendo linguagem C
// apenas (bem como algumas directivas de pré-processamento indicando a
// proveniência das linhas de código). A este ficheiro contendo apenas
// linguagem C (ou quase), damos o nome de _unidade de compilação_.
// Usualmente as unidades de compilação não têm senão uma existência efémera,
// podendo mesmo não chegar a existir enquanto ficheiros no sistema de
// ficheiros do computador.
//
// 2. Compilar cada um dos ficheiros resultantes do pré-processamento, ou seja,
// compilar cada uma das unidades de compilação. A compilação é o processo de
// tradução da linguagem C para a linguagem máquina do computador em causa. O
// resultado da compilação de uma unidade de compilação é um _ficheiro
// objecto_. Os ficheiros objecto têm, em Linux, a extensão `.o`. Em Windows
// é típico a extensão ser `.obj`. Os ficheiros objecto não são ainda
// executáveis, pois tipicamente cada ficheiro objecto contêm código máquina
// que recorre a ferramentas externas a esse ficheiro objecto.
//
// 3. Depois de gerados os ficheiros objecto, estes têm de ser fundidos num
// único ficheiro executável. A fusão resolve as dependências entre os vários
// ficheiro objecto e entre estes e colecções de ficheiros objecto arquivados
// em _bibliotecas_. As bibliotecas, em Linux, têm a extensão `.a` (de
// _archive_), quando estáticas, ou `.so`, quando dinâmicas. Em Windows as
// extensões correspondentes são `.lib` e `.dll`. O resultado de uma fusão
// com sucesso é um ficheiro executável. Em Linux os ficheiros executáveis
// podem ser qualquer extensão. Em Windows, a extensão de um ficheiro
// executável é `.exe`.

// Inclusão de ficheiros de cabeçalho
// ----------------------------------
//
// É usual os ficheiros `.c`, ou seja, os ficheiros que são pré-processados, se
// iniciem com a inclusão de um conjunto de _ficheiros de cabeçalho_ padrão.
// Cada uma destas inclusões é realizada pelo pré-processador quando encontra a
// directiva de pré-processamento `#include`. Esta directiva é obrigatoriamente
// seguida do nome do ficheiro de cabeçalho a incluir. Este nome coloca-se entre
// parênteses agudos (`<>`) quando os ficheiros a incluir se encontram nas
// pastas de ficheiros de cabeçalho padrão e entre aspas (`""`) quando estes se
// encontram na mesma pasta do ficheiro `.c` em pré-processamento.
//
// Os ficheiros de cabeçalho, também conhecidos por _ficheiros de interface_,
// contêm sobretudo _declarações_ e, ocasionalmente, também definições,
// necessárias para que o código presente no ficheiro que os inclui possa
// recorrer a ferramentas _definidas_ noutros locais. A diferença entre
// _declaração_ e _definição_ é subtil. Geralmente, uma declaração limita-se a
// dar a conhecer ao leitor ou ao compilador a existência de uma dada entidade
// (e.g., uma rotina ou uma estrutura), sem a definir. Uma definição é sempre
// também uma declaração, mas não se limita a declarar a existência de algo:
// define-o de forma completa. As declarações estão, por isso, associadas às
// interfaces das ferramentas declaradas e a definições à sua implementação.
//
// Neste caso particular incluímos dois dos ficheiros de cabeçalho da biblioteca
// padrão do C, i.e., da biblioteca que acompanha a linguagem C tal como
// definida pela sua norma:
//
// - `stdio.h` &ndash; Declara os procedimentos `printf()` e `scanf()`, usados
// respectivamente para escrever no ecrã (ou melhor, no canal de saída) e
// para ler do teclado (ou melhor, do canal de entrada).
//
// - `stdlib.h` &ndash; Define a _macro_ `EXIT_SUCCESS`, que é usada para
// assinalar sucesso na execução de um programa, quando este termina, ou
// seja, quando se _sai_ do programa.
//
#include <stdio.h>
#include <stdlib.h>

// Definição da função `factorial()`
// ---------------------------------
//
// Em C é possível «empacotar» código para o poder usar em vários locais. Ao
// código assim «empacotado» chama-se um _rotina_. As rotinas em C podem ser
// _funções_, se não alterarem o mundo, limitando-se a resultar num valor, ou
// _procedimentos_, se agirem sobre algum aspecto do programa ou do mundo que o
// rodeia, provocando potencialmente alterações. Neste caso estamos a definir
// uma função chamada `factorial()`.
//
// A interface de uma rotina diz _como a rotina se usa_ e _o que a rotina faz ou
// calcula_. Pelo contrário, a implementação de uma rotina especifica _como a
// rotina funciona_. A definição de uma rotina, seja ela função ou procedimento,
// consiste numa interface, que corresponde ao chamado _cabeçalho_ da rotina, e
// numa implementação, que corresponde ao chamado _corpo_ dessa mesma rotina.
  
// ### Cabeçalho da função `factorial()`
//
// O cabeçalho de uma rotina é parte da sua _interface_. Ou seja, daquilo que é
// necessário conhecer para a conseguir utilizar. O cabeçalho de uma rotina
// indica:
//
// - O seu nome &ndash; Neste caso o nome é `factorial`, pois é suposto esta
// função calcular e devolver o factorial do valor que lhe for _passado_ como
// _argumento_.
//
// - A lista dos seus _parâmetros_, incluindo o tipo e o nome de cada uma desses
// _parâmetros_ &ndash; Os _parâmetros_ são _variáveis locais_ (i.e., visíveis
// apenas num contexto local, e.g., no corpo de uma rotina), _automáticas_
// (i.e., construídas ao entrar no respectivo contexto e destruídas ao dele
// sair), que têm a particularidade de ser inicializadas com o valor do
// _argumento_ correspondente sempre que a rotina é _executada_ como resultado
// de uma sua _invocação_.
//
// - O tipo do valor _devolvido_ quando a rotina _retorna_ &ndash; As funções
// (bem como alguns procedimentos) são invocadas para se obter um dado valor
// como resultado. Esse valor é calculado pela rotina e _devolvido_ quando a
// rotina terminar, i.e., quando se _retorna_ ao local onde essa rotina foi
// invocada.
//
// A função `factorial()` recebe um `int` como argumento. Esse `int` é guardado
// dentro do parâmetro `n`, que, aliás, é uma _constante_, pois o _qualificador_
// `const` altera a natureza de `n`, que deixa de ser uma variável e se torna
// constante. É muito importante perceber a diferença entre um _argumento_, que
// é uma expressão ou valor passado quando se _invoca_ uma rotina, e um
// _parâmetro_, que é uma variável ou constante especial que, no início da
// execução da rotina, é inicializada automaticamente com o valor do argumento
// passado aquando da invocação da mesma rotina. Mais abaixo se verão invocações
// desta função.
//
// Quando a função `factorial()` termina, altura em que o fluxo de execução
// _retorna_ ao ponto de invocação, _devolve_ um valor. Esse valor é o factorial
// do valor recebido como argumento, e é do tipo `int`, neste caso. Isso é
// indicado pela presença da _palavra-chave_ `int` antes do nome da função _no
// cabeçalho da definição da função_.
int factorial(const int n)
// ### Corpo da função `factorial()`
//
// O corpo de uma rotina contém a sua implementação. Em C, o corpo de uma rotina
// consiste sempre num _bloco de instruções_, ou seja, numa sequência de
// instruções envoltas por chavetas.
//
// A implementação que usamos para a função `factorial()` nasce numa definição
// recursiva da noção de factorial.
//
// O factorial de um número ![n](http://bit.ly/Z4ELdk) representa-se por
// ![n](http://bit.ly/Z4ELdk) e corresponde ao produto de todos os números
// inteiros entre 0 e ![n](http://bit.ly/Z4ELdk), se
// ![n>0](http://bit.ly/ZteSVa), tendo, por definição, o valor 1 quando
// ![n=0](http://bit.ly/10afb7o). Ou seja, se ![n>0](http://bit.ly/ZteSVa),
// ![n!=n(n-1)...1](http://bit.ly/12553hX). É fácil concluir daqui que
// ![n!=n(n-1)!](http://bit.ly/113hsrr), desde que ![n>0](http://bit.ly/ZteSVa).
// Ou seja,
//
// ![Definição recursiva do factorial](http://bit.ly/18B6xTd)
//
// A implementação é consequência directa desta definição.
//
// Note que esta função não faz qualquer esforço para lidar com valores
// inválidos do seu argumento. Se se passar à função um valor negativo ou um
// valor cujo factorial seja demasiado grande para representar num `int`, a
// função pura e simplesmente não funciona. Isto é um erro de programação,
// naturalmente. Uma forma de resolver este erro seria:
//
// 1. Incluir no topo deste ficheiro, para além dos ficheiros de cabeçalho já
// incluídos, o ficheiro de cabeçalho `assert.h`.
//
// 2. Alterar o corpo da função se modo a fazer a verificação da validade do seu
// argumento usando uma rotina especial (na realidade uma _macro_ do
// pré-processador) chamada `assert()`:
//
// ```C
// {
//          assert(0 <= n && n <= 12);
//
//          if (n == 0)
//                  return 1;
//          return n * factorial(n - 1);
// }
// ```
//
// Note que o limite superior para o valor do argumento é muito baixo: 12. Isso
// deve-se a dois factos:
//
// 1. Os `int` em C, nos nossos ambientes típicos, são guardados em apenas 32
// _bit_ interpretados em complemento para dois, pelo que um inteiro só pode
// tomar valores entre ![-2^31](http://bit.ly/16CVI6B) e
// ![2^31-1](http://bit.ly/12AavZ0), ou seja, entre
// -2&thinsp;147&thinsp;483&thinsp;648 e 2&thinsp;147&thinsp;483&thinsp;647.
//
// 2. O factorial é uma função de crescimento muito rápido, pelo que 13!, com o
// valor 6&thinsp;227&thinsp;020&thinsp;800, excede já o limite superior dos
// `int`.

//
{
// Começamos por verificar se se aplica o caso especial em que o valor de `n` é
// zero.
	if (n == 0)
// Se se aplicar, retorna-se imediatamente (i.e., termina-se a função,
// retornando ao ponto de invocação) _devolvendo_ o valor 1.
		return 1;
// No caso contrário, retorna-se devolvendo o produto entre o valor de `n` e o
// valor devolvido por... uma nova invocação da mesma função, embora com um
// valor mais pequeno passado como argumento, ou seja, _n - 1_ em vez de _n_. A
// uma invocação deste tipo chama-se uma _invocação recursiva_. Note-se que o
// funcionamento desta função decorre do facto de, cada vez que a função é
// invocada, as respectivas variáveis locais serem construídas na _pilha_ (uma
// zona especial da memória de um _processo_ em execução). Isso significa que,
// durante a execução da função decorrente de uma invocação `factorial(4)`, por
// exemplo, chega a haver cinco instâncias ou versões do parâmetro _n_ em
// existência _em simultâneo_.
	return n * factorial(n - 1);
}

// A rotina principal `main()`
// ---------------------------
//
// Todos os programas escritos em C têm de definir um procedimento `main()`,
// i.e., com o nome `main`. A execução de um programa escrito em C começa sempre
// com a invocação dessa rotina, que por isso é o ponto de entrada no programa.
//
// O nosso programa tem como objectivo calcular o factorial de um valor
// introduzido pelo utilizador no teclado. Um possível exemplo de interacção do
// programa com o utilizador é o seguinte:
//
// ```
// mises:hello_world mmsequeira$ bin/Debug/hello_world 
// Hello world! Let's calculate the factorial of a number.
// Please enter a non-negative integer: 10
// 10! = 3628800
// ```
//
// Tal como referido anteriormente, este programa está errado, pois não faz
// qualquer tentativa de lidar com erros do utilizador. Por exemplo, se o
// utilizador não introduzir um número, mas sim o seu nome, o resultado é
// inesperado:
//
// ```
// mises:hello_world mmsequeira$ bin/Debug/hello_world 
// Hello world! Let's calculate the factorial of a number.
// Please enter a non-negative integer: Manuel
// 32767! = 0
// ```
//
// Note que o valor 32767 nada tem de especial. Quando uma leitura falha, é
// usual que a variável na qual se guardaria o valor lido seja deixada sem
// qualquer alteração. Não tendo sido inicializada, o valor que contém é
// indefinido, no sentido em que pode ser qualquer valor inteiro. O facto de o
// valor ter sido 32767 reflecte apenas o ambiente particular de compilação e
// execução do programa usado ao gerar esta documentação.
//
// Também ocorre um erro, embora de outro tipo, se o utilizador introduzir um
// valor negativo:
//
// ```
// mises:hello_world mmsequeira$ bin/Debug/hello_world
// Hello world! Let's calculate the factorial of a number.
// Please enter a non-negative integer: -1
// Segmentation fault: 11
// ```
//
// Neste caso o erro ocorre porque, partindo de um valor negativo, só se
// atingiria o caso especial da definição recursiva, i.e., o caso em que o
// argumento da função é 0, depois de passar por todos os possíveis valores
// negativos e positivos dos inteiros (quando se subtrai um ao mais pequeno dos
// inteiros obtém-se o maior dos inteiros, por estranho que pareça). Trata-se de
// um número demasiado grande de execuções recursivas todas _em curso_, pelo que
// o espaço de memória, chamado «pilha» (_stack_), reservado pelo sistema
// operativo para guardar informação sobre as rotinas em execução, incluindo as
// respectivas variáveis locais, acaba por se esgotar, levando o programa a
// _abortar_.
//
// Finalmente, outro erro deste programa é não fazer qualquer esforço para
// verificar se o valor máximo dos valores do tipo _int_ é ultrapassado durante
// o cálculo do factorial. Isso leva, mais uma vez, a resultados inesperados,
// mesmo perante respostas aparentemente válidas do utilizador:
//
// ```
// mises:hello_world mmsequeira$ bin/Debug/hello_world 
// Hello world! Let's calculate the factorial of a number.
// Please enter a non-negative integer: 17
// 17! = -288522240
// ```
//
// Em todos estes casos, mesmo nos dois primeiros, trata-se de erros de
// programação: um programa _tem_ de saber lidar com os seus próprios limites e
// com quaisquer erros do utilizador. Se não o fizer, _está errado_. Ou seja,
// este programa _está errado_, pois optámos por não fazer qualquer verificação
// de erros, de modo a mantê-lo simples.
//
// Uma versão correcta do código é apresentada mais abaixo, com alguns
// comentários.
  
// Neste caso declaramos a rotina como não possuindo qualquer parâmetro: daí a
// palavra-chave `void` que colocámos entre parênteses após o nome da rotina.
// (Note- se, o entanto, que poderíamos ter declarado a rotina de forma
// diferente, de modo a poder receber argumentos vindos da linha de comandos.)
//
// Declaramos também a rotina como devolvendo um valor do tipo `int`. Este tipo
// de devolução é obrigatório, no caso da rotina `main()`. O valor devolvido
// pela rotina quando retorna é usado pela entidade que executou o programa para
// saber se a execução teve ou não sucesso.
int main(void)
{
	// Começamos por escrever no ecrã o nome e o propósito do programa. Para
	// isso, invocamos o procedimento `printf()` passando-lhe como argumento
	// uma _cadeia de caracteres_, neste caso uma _cadeia de caracteres
	// literal_, pois usamos a notação do C das cadeias de caracteres
	// literais. Ou seja, uma sequência de caracteres escritos entre aspas.
	// O único caso especial aqui é o da sequência de caracteres `\n`.
	// Quando o C encontra o caractere `\` numa cadeia de caracteres, não o
	// interpreta literalmente: escapa para um modo de interpretação
	// diferente, em que os caracteres que se sequem ao `\` têm um
	// significado especial. Neste caso usamos a sequência `\n`, que
	// significa o caractere _fim-de-linha_. Este caractere termina a linha
	// corrente e dá início a uma nova linha de caracteres no ecrã.
	printf("Hello world! Let's calculate the factorial of a number.\n");

	// Uma vez que o objectivo do programa é calcular o factorial de um
	// número, começamos por pedir ao utilizador para introduzir um número
	// inteiro não negativo. Note que neste caso não terminamos a linha,
	// pois pretendemos que a resposta do utilizador surja visualmente à
	// frente do texto que escrevemos. Em vez disso, escrevemos um espaço,
	// para que o número introduzido pelo utilizador não surja «colado» ao
	// nosso texto. Note ainda que a leitura dos caracteres introduzidos
	// pelo utilizador só é realizada depois de este carregar em «enter», o
	// que terá o efeito visual de terminar esta linha.
	printf("Please enter a non-negative integer: ");

	// Antes de proceder à leitura propriamente dita, temos de definir uma
	// variável para guardar o valor introduzido pelo utilizador. Chamamos a
	// essa variável `number` e atribuímos-lhe o tipo _int_, compatível com
	// o parâmetro de entrada da função _factorial()_ já definida. A
	// definição de uma variável em C começa sempre por um tipo. Nos casos
	// mais simples, esse tipo é seguido do nome da variável em definição,
	// tal como fazemos aqui. Este formato de definição é exactamente o
	// mesmo que usámos no cabeçalho da função `factorial()`, aliás.
	int number;

	// Para proceder à leitura do número introduzido pelo utilizador
	// invocamos o procedimento `scanf()`, passando-lhe dois argumentos. O
	// primeiro é uma cadeia de caracteres literal a que se chama _formato_
	// e que contém uma chamada _especificação de conversão_, iniciada pelo
	// caractere `&`. A leitura é controlada por esta cadeia. Quando o
	// procedimento encontra a especificação de conversão `%d`, procede à
	// leitura dos próximos caracteres da entrada admitindo que estes
	// correspondem à representação decimal usual de um número inteiro.
	scanf("%d", &number);

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
	// execução teve sucesso (ou pelo menos admite-se que sim...),
	// devolvemos o valor especial `EXIT_SUCCESS` ao retornar.
	return EXIT_SUCCESS;
}

// O código tal como está tem erros, como vimos. Uma versão completa (e
// complexa!) do código com todos os erros corrigidos (esperamos!) é a seguinte
// (ver também [`hello_world_correct.c`](hello_world_correct.c.html)):
//
// ```C
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <assert.h>
// 
// int factorial(const int n)
// {
//         assert(0 <= n && n <= 12);
// 
//         if (n == 0)
//                 return 1;
//         return n * factorial(n - 1);
// }
// 
// int main(void)
// {
//         printf("Hello world! Let's calculate the factorial of a number.\n");
// 
//         int number;
//         while(true) {
//                 printf("Please enter a non-negative integer "
//                        "between 0 and 12: ");
//                 if (scanf("%d", &number) == 1 && 0 <= number && number <= 12)
//                         break;
//                 if (feof(stdin) || ferror(stdin)) {
//                         fprintf(stderr,
//                                 "Unrecoverable error reading user response. "
//                                 "Exiting.\n");
//                         return EXIT_FAILURE;
//                 }
//                 printf("Invalid response. Try again.\n");
//                 scanf("%*[^\n]%*1[\n]");
//         }
// 
//         printf("%d! = %d\n", number, factorial(number));
// 
//         return EXIT_SUCCESS;
// }
// ```
//
// Alguns comentários:
//
// 1. É um bom exercício sobre a linguagem C tentar compreender este código do
// princípio ao fim.
//
// 2. A inclusão de `stdbool.h` deve-se à necessidade de usar o valor booleano
// `true` como _guarda_ do ciclo `while`.
//
// 3. A leitura do valor do teclado é feita dentro de um ciclo que permite ao
// utilizador corrigir os seus próprios erros.
//
// 4. O ciclo usado é um _ciclo infinito_ que, ao contrário do que o nome
// sugere, termina logo que o utilizador introduza um valor válido. A utilização
// de um ciclo infinito `while(true)` deve-se ao facto de as condições de
// paragem do ciclo se encontrarem a meio do seu _passo_.
//
// 5. O ciclo tem duas condições de paragem. A primeira ocorre quando a leitura
// tem sucesso e o valor lido é válido. A função `scanf()` devolve o número de
// atribuições a itens de entrada realizadas com sucesso. No nosso caso podemos
// saber se foi lido um valor inteiro com sucesso verificando se o valor
// devolvido foi 1. Para saber se o valor lido é válido, verificamos se se
// encontra entre 0 e 12. Caso tudo tenha corrido bem, o ciclo é interrompido
// através da instrução `break`.
//
// 6. A segunda condição de paragem ocorre quando, depois de termos tentado ler
// e de não termos tido sucesso, verificamos que o canal de leitura `stdin`
// ficou marcado como tendo sido atingido o fim do ficheiro (a entrada de um
// programa pode ser redireccionada de modo a ser feita a partir de um ficheiro)
// ou tendo ocorrido um outro erro de leitura. Nesse caso terminamos o programa
// devolvendo o valor especial `EXIT_FAILURE` para comunicar este erro à
// entidade que executou o programa, isto depois de escrevermos uma mensagem de
// erro apropriada no canal de escrita de erros `stderr`.
//
// 7. Quando detectamos um erro de leitura não fatal, avisamos o utilizador do
// problema e, depois de descartar a linha errónea introduzida pelo utilizador,
// repetimos o passo do ciclo.
//
// 8. Para descartar uma linha completa de caracteres, invocamos o procedimento
// `scanf()` com a cadeia de formação `%*[^\n]%*1[\n]`. O significado é o
// seguinte:
//
//   - Primeira especificação de conversão, `%*[^\n]`: Ler _e descartar_ (daí o
//     caractere `*`) todos os caracteres até o próximo fim-de-linha, exclusive.
//
//   - Segunda especificação de conversão, `%*1[\n]`: Ler _e descartar_ (daí o
//     caractere `*`) exactamente um caractere fim-de-linha. Colocar `\n` na
//     cadeia de formatação em vez desta especificação de conversão não teria o
//     resultado pretendido, pois o procedimento `scanf()` interpreta todos os
//     caracteres «brancos» como uma ordem para ignorar um número arbitrário de
//     caracteres brancos até ser encontrado o primeiro caractere não branco, o
//     que levaria a que não surgisse novo pedido de inserção de um número
//     válido enquanto o utilizador fosse carregando em «enter».
//
// Se tudo isto lhe pareceu complexo, não se preocupe: é mesmo complexo. :-)