// Estrutura de um programa em C
// =============================
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
//    que lê um ficheiro contendo código C e directivas de pré-processamento e
//    interpreta estas directivas, produzindo um ficheiro contendo linguagem C
//    apenas (bem como algumas directivas de pré-processamento indicando a
//    proveniência das linhas de código). A este ficheiro contendo apenas
//    linguagem C (ou quase), damos o nome de _unidade de compilação_.
//    Usualmente as unidades de compilação não têm senão uma existência efémera,
//    podendo mesmo não chegar a existir enquanto ficheiros no sistema de
//    ficheiros do computador.
//
// 2. Compilar cada um dos ficheiros resultantes do pré-processamento, ou seja,
//    compilar cada uma das unidades de compilação. A compilação é o processo de
//    tradução da linguagem C para a linguagem máquina do computador em causa. O
//    resultado da compilação de uma unidade de compilação é um _ficheiro
//    objecto_. Os ficheiros objecto têm, em Linux, a extensão `.o`. Em Windows
//    é típico a extensão ser `.obj`. Os ficheiros objecto não são ainda
//    executáveis, pois tipicamente cada ficheiro objecto contêm código máquina
//    que recorre a ferramentas externas a esse ficheiro objecto.
//
// 3. Depois de gerados os ficheiros objecto, estes têm de ser fundidos num
//    único ficheiro executável. A fusão resolve as dependências entre os vários
//    ficheiro objecto e entre estes e colecções de ficheiros objecto arquivados
//    em _bibliotecas_. As bibliotecas, em Linux, têm a extensão `.a` (de
//    _archive_), quando estáticas, ou `.so`, quando dinâmicas. Em Windows as
//    extensões correspondentes são `.lib` e `.dll`. O resultado de uma fusão
//    com sucesso é um ficheiro executável. Em Linux os ficheiros executáveis
//    podem ser qualquer extensão. Em Windows, a extensão de um ficheiro
//    executável é `.exe`.

// Inclusão de ficheiros de cabeçalho
// ----------------------------------
//
// É usual os ficheiros `.c`, ou seja, os ficheiros que são pré-processados, se
// É iniciem com !!!!!!!!!!!!!!

#include <stdio.h>
#include <stdlib.h>

int factorial(const int n)
{
	if (n == 0)
		return 1;
	return n * factorial(n - 1);
}

int main(void)
{
	printf("Hello world! Let's calculate the factorial of a number.\n");

	printf("Please enter a non-negative integer: ");

	int number;

	scanf("%d", &number);

	printf("%d! = %d\n", number, factorial(number));

	return EXIT_SUCCESS;
}
