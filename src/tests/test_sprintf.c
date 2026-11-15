#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(sprintf_percent_and_text) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int s21_res = s21_sprintf(s21_buf, "Hello, World! 100%%");
  int std_res = sprintf(std_buf, "Hello, World! 100%%");

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(sprintf_char) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int s21_res = s21_sprintf(s21_buf, "Char: %c, Null: %c", 'A', '\0');
  int std_res = sprintf(std_buf, "Char: %c, Null: %c", 'A', '\0');

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_mem_eq(s21_buf, std_buf, std_res + 1);
}
END_TEST

START_TEST(sprintf_string) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int s21_res = s21_sprintf(s21_buf, "String: %s, Empty: %s", "School 21", "");
  int std_res = sprintf(std_buf, "String: %s, Empty: %s", "School 21", "");

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(sprintf_integer) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int val1 = 42;
  int val2 = -12345;
  int val3 = 0;

  int s21_res = s21_sprintf(s21_buf, "Nums: %d, %i, %d", val1, val2, val3);
  int std_res = sprintf(std_buf, "Nums: %d, %i, %d", val1, val2, val3);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(sprintf_float) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  double f1 = 3.141592;
  double f2 = -0.00045;
  double f3 = 123.456;

  int s21_res = s21_sprintf(s21_buf, "Floats: %f, %f, %.2f", f1, f2, f3);
  int std_res = sprintf(std_buf, "Floats: %f, %f, %.2f", f1, f2, f3);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(sprintf_width_flags) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int num = 7;
  int s21_res = s21_sprintf(s21_buf, "Width: |%10d| and |%-10d|", num, num);
  int std_res = sprintf(std_buf, "Width: |%10d| and |%-10d|", num, num);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(sprintf_sign_flags) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int pos = 55;
  int neg = -55;

  int s21_res =
      s21_sprintf(s21_buf, "Signs: %+d, %+d, % d, % d", pos, neg, pos, neg);
  int std_res =
      sprintf(std_buf, "Signs: %+d, %+d, % d, % d", pos, neg, pos, neg);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(sprintf_hex_octal) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  unsigned int val = 255;

  int s21_res = s21_sprintf(s21_buf, "Hex: %x, %X, Oct: %o", val, val, val);
  int std_res = sprintf(std_buf, "Hex: %x, %X, Oct: %o", val, val, val);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

Suite* test_sprintf_suite(void) {
  Suite* s = suite_create("S21_SPRINTF");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, sprintf_percent_and_text);
  tcase_add_test(tc, sprintf_char);
  tcase_add_test(tc, sprintf_string);
  tcase_add_test(tc, sprintf_integer);
  tcase_add_test(tc, sprintf_float);
  tcase_add_test(tc, sprintf_width_flags);
  tcase_add_test(tc, sprintf_sign_flags);
  tcase_add_test(tc, sprintf_hex_octal);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  int failed = 0;
  Suite* s = test_sprintf_suite();
  SRunner* runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? 0 : 1;
}