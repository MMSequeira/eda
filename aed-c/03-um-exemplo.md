Um programa simples (ou nem tanto...)
=====================================

Teste:		

```C
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
 
	int n;
 
	scanf("%d", &n);
 
	printf("%d! = %d\n", n, factorial(n));
 
	return EXIT_SUCCESS;
}
```