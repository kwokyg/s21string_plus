#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memchr) {
  const char str[] = "School 21! \0 hidden";
  ck_assert_ptr_eq(s21_memchr(str, '2', 10), memchr(str, '2', 10));
  ck_assert_ptr_eq(s21_memchr(str, 'z', 10), memchr(str, 'z', 10));
  ck_assert_ptr_eq(s21_memchr(str, 'h', 18), memchr(str, 'h', 18));
  ck_assert_ptr_eq(s21_memchr(str, 'S', 0), memchr(str, 'S', 0));
}
END_TEST

START_TEST(test_memcmp) {
  const char s1[] = "Hello\0World";
  const char s2[] = "Hello\0Earth";
  ck_assert_int_eq(s21_memcmp(s1, s2, 6), memcmp(s1, s2, 6));
  ck_assert_int_eq(s21_memcmp(s1, s2, 10) > 0, memcmp(s1, s2, 10) > 0);
  ck_assert_int_eq(s21_memcmp(s2, s1, 10) < 0, memcmp(s2, s1, 10) < 0);
  ck_assert_int_eq(s21_memcmp(s1, s2, 0), memcmp(s1, s2, 0));
}
END_TEST

START_TEST(test_memcpy) {
  char b1[20] = "1234567890";
  char b2[20] = "1234567890";
  const char src[] = "ABC\0DEF";
  ck_assert_ptr_eq(s21_memcpy(b1, src, 7), b1);
  memcpy(b2, src, 7);
  ck_assert_mem_eq(b1, b2, 10);
  s21_memcpy(b1, "XYZ", 0);
  memcpy(b2, "XYZ", 0);
  ck_assert_mem_eq(b1, b2, 10);
}
END_TEST

START_TEST(test_memset) {
  char b1[20] = "Hello world";
  char b2[20] = "Hello world";
  s21_size_t zero = 0;
  ck_assert_ptr_eq(s21_memset(b1, 'x', 5), b1);
  memset(b2, 'x', 5);
  ck_assert_str_eq(b1, b2);
  s21_memset(b1, 'y', zero);
  memset(b2, 'y', zero);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_strlen) {
  ck_assert_uint_eq(s21_strlen("Hello, School 21!"),
                    strlen("Hello, School 21!"));
  ck_assert_uint_eq(s21_strlen(""), strlen(""));
  ck_assert_uint_eq(s21_strlen("abc\0def"), strlen("abc\0def"));
}
END_TEST

START_TEST(test_strncat) {
  char b1[30] = "Hello";
  char b2[30] = "Hello";
  ck_assert_ptr_eq(s21_strncat(b1, ", World!", 15), b1);
  strncat(b2, ", World!", 15);
  ck_assert_str_eq(b1, b2);

  s21_strncat(b1, "12345", 3);
  strncat(b2, "12345", 3);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_strncpy) {
  char b1[20] = "1111111111";
  char b2[20] = "1111111111";
  const char* long_src = "LongString";
  s21_size_t n = 4;
  ck_assert_ptr_eq(s21_strncpy(b1, "Hi", 6), b1);
  strncpy(b2, "Hi", 6);
  ck_assert_mem_eq(b1, b2, 10);

  s21_strncpy(b1, long_src, n);
  strncpy(b2, long_src, n);
  ck_assert_mem_eq(b1, b2, 10);
}
END_TEST

START_TEST(test_strncmp) {
  ck_assert_int_eq(s21_strncmp("abcdef", "abcxyz", 3),
                   strncmp("abcdef", "abcxyz", 3));
  ck_assert_int_eq(s21_strncmp("abcdef", "abcxyz", 5) < 0,
                   strncmp("abcdef", "abcxyz", 5) < 0);
  ck_assert_int_eq(s21_strncmp("abcxyz", "abcdef", 5) > 0,
                   strncmp("abcxyz", "abcdef", 5) > 0);
  ck_assert_int_eq(s21_strncmp("", "", 5), strncmp("", "", 5));
  ck_assert_int_eq(s21_strncmp("abc", "xyz", 0), strncmp("abc", "xyz", 0));
}
END_TEST

START_TEST(test_strchr) {
  const char str[] = "School 21";
  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));
}
END_TEST

START_TEST(test_strrchr) {
  const char str[] = "School 21";
  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
  ck_assert_ptr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

START_TEST(test_strcspn) {
  ck_assert_uint_eq(s21_strcspn("hello123", "123"), strcspn("hello123", "123"));
  ck_assert_uint_eq(s21_strcspn("hello", "xyz"), strcspn("hello", "xyz"));
  ck_assert_uint_eq(s21_strcspn("hello", "h"), strcspn("hello", "h"));
  ck_assert_uint_eq(s21_strcspn("", "abc"), strcspn("", "abc"));
}
END_TEST

START_TEST(test_strpbrk) {
  const char str[] = "hello world 21";
  ck_assert_ptr_eq(s21_strpbrk(str, "123"), strpbrk(str, "123"));
  ck_assert_ptr_eq(s21_strpbrk(str, "xyz"), strpbrk(str, "xyz"));
  ck_assert_ptr_eq(s21_strpbrk("", "abc"), strpbrk("", "abc"));
}
END_TEST

START_TEST(test_strstr) {
  const char str[] = "Hello, School 21!";
  ck_assert_ptr_eq(s21_strstr(str, "School"), strstr(str, "School"));
  ck_assert_ptr_eq(s21_strstr(str, ""), strstr(str, ""));
  ck_assert_ptr_eq(s21_strstr(str, "42"), strstr(str, "42"));
  ck_assert_ptr_eq(s21_strstr("", "a"), strstr("", "a"));
}
END_TEST

START_TEST(test_strtok) {
  char s1[] = ",,one,two..three/four,";
  char s2[] = ",,one,two..three/four,";
  const char delim[] = ",./";

  char* t1 = s21_strtok(s1, delim);
  char* t2 = strtok(s2, delim);
  while (t1 != S21_NULL || t2 != NULL) {
    ck_assert_str_eq(t1, t2);
    t1 = s21_strtok(S21_NULL, delim);
    t2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(t1, t2);
}
END_TEST

START_TEST(test_strerror) {
  for (int i = -2; i <= 135; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

Suite* part1_suite(void) {
  Suite* s = suite_create("Part_1");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memchr);
  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_memcpy);
  tcase_add_test(tc_core, test_memset);
  tcase_add_test(tc_core, test_strlen);
  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strncpy);
  tcase_add_test(tc_core, test_strncmp);
  tcase_add_test(tc_core, test_strchr);
  tcase_add_test(tc_core, test_strrchr);
  tcase_add_test(tc_core, test_strcspn);
  tcase_add_test(tc_core, test_strpbrk);
  tcase_add_test(tc_core, test_strstr);
  tcase_add_test(tc_core, test_strtok);
  tcase_add_test(tc_core, test_strerror);

  suite_add_tcase(s, tc_core);
  return s;
}