#include <check.h>

Suite* part1_suite(void);
Suite* test_sprintf_suite(void);

int main(void) {
  int failed = 0;
  SRunner* sr = srunner_create(part1_suite());
  srunner_add_suite(sr, test_sprintf_suite());

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? 0 : 1;
}