// `rationals_with_structs.c` &ndash; Racionais com estruturas C
// =============================================================

#include <stdio.h>
#include <stdlib.h>

struct rational {
	int numerator;
	int denominator;
};

struct rational RAT_symmetric_of(struct rational r)
{
	struct rational result = {
		numerator: -r.numerator,
		denominator: r.denominator
	};
	return result;
}

void RAT_println(struct rational r)
{
	printf("%d/%d\n", r.numerator, r.denominator);
}

int main(void)
{
	struct rational r1 = { numerator: 1, denominator: 2};
	// rational r2 = -r1;
	struct rational r2 = RAT_symmetric_of(r1);

	RAT_println(r1);
	RAT_println(r2);

	return EXIT_SUCCESS;
}
