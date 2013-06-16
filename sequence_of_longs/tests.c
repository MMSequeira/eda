// `experiments.c` &ndash; Testes das sucessões de `long`
// ======================================================

#include <stdlib.h>
#include <check.h>

START_TEST(one_plus_one_equals_two_test)
{
	fail_unless(1 + 1 == 3, "One plus one should always equal 3.");
}
END_TEST

Suite *sequence_of_longs_suite(void)
{
	Suite *suite = suite_create("Sequence of longs");
	TCase *core_test_case = tcase_create("Core");
	tcase_add_test(core_test_case, one_plus_one_equals_two_test);
	suite_add_tcase(suite, core_test_case);

	return suite;
}

int main_tests(void)
{
	Suite *suite = sequence_of_longs_suite();
	SRunner *suite_runner = srunner_create(suite);
	srunner_run_all(suite_runner, CK_VERBOSE);
	int number_of_failed_tests = srunner_ntests_failed(suite_runner);
	srunner_free(suite_runner);
	return (number_of_failed_tests == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
