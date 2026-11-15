#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

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

  int s21_res =
      s21_sprintf(s21_buf, "Char: %c, Width: |%5c| |%-5c|", 'A', 'B', 'C');
  int std_res =
      sprintf(std_buf, "Char: %c, Width: |%5c| |%-5c|", 'A', 'B', 'C');

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(sprintf_string) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  int s21_res = s21_sprintf(s21_buf, "Str: %s, Prec: %.3s, Pad: |%10s| |%-10s|",
                            "School 21", "School", "Hi", "Hi");
  int std_res = sprintf(std_buf, "Str: %s, Prec: %.3s, Pad: |%10s| |%-10s|",
                        "School 21", "School", "Hi", "Hi");

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

  int s21_res =
      s21_sprintf(s21_buf, "Nums: %d, %d, %.5d, %.0d", val1, val2, val1, val3);
  int std_res =
      sprintf(std_buf, "Nums: %d, %d, %.5d, %.0d", val1, val2, val1, val3);

  ck_assert_int_eq(s21_res, std_res);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(sprintf_unsigned_and_length) {
  char s21_buf[150] = {0};
  char std_buf[150] = {0};

  unsigned int u1 = 4294967295U;
  short int h1 = -32000;
  long int l1 = 214748364700L;
  unsigned short uh1 = 65000;
  unsigned long ul1 = 9876543210UL;

  int s21_res = s21_sprintf(s21_buf, "U:%u H:%hd L:%ld UH:%hu UL:%lu", u1, h1,
                            l1, uh1, ul1);
  int std_res =
      sprintf(std_buf, "U:%u H:%hd L:%ld UH:%hu UL:%lu", u1, h1, l1, uh1, ul1);

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

  int s21_res =
      s21_sprintf(s21_buf, "Floats: %f, %f, %.2f, %.0f", f1, f2, f3, f3);
  int std_res = sprintf(std_buf, "Floats: %f, %f, %.2f, %.0f", f1, f2, f3, f3);

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

Suite* test_sprintf_suite(void) {
  Suite* s = suite_create("S21_SPRINTF");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, sprintf_percent_and_text);
  tcase_add_test(tc, sprintf_char);
  tcase_add_test(tc, sprintf_string);
  tcase_add_test(tc, sprintf_integer);
  tcase_add_test(tc, sprintf_unsigned_and_length);
  tcase_add_test(tc, sprintf_float);
  tcase_add_test(tc, sprintf_width_flags);
  tcase_add_test(tc, sprintf_sign_flags);

  suite_add_tcase(s, tc);
  return s;
}