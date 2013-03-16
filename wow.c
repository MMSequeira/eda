#include <stdio.h>
#include <stdlib.h>

int main_wow(void)
{
	// Don't do this at home!
	int m[] = {1, 2, 3};

	for (int i = 0; i != 3; i++)
//		printf("%d\n", m[i]);
//		printf("%d\n", *(m + i));
//		printf("%d\n", *(i + m));
		printf("%d\n", i[m]);

	for (int i = 0; i != 5; i++)
//		putchar("Hello"[i]);
		putchar(i["Hello"]);

	return EXIT_SUCCESS;
}
