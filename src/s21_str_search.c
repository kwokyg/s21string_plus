#include "s21_string.h"

char* s21_strchr(const char* str, int c) {
  s21_size_t i = 0;
  while (str[i] != (char)c) {
    if (str[i] == '\0') {
      return S21_NULL;
    }
    i++;
  }

  return (char*)(str + i);
}

char* s21_strrchr(const char* str, int c) {
  const char* last = S21_NULL;
  while (*str != '\0') {
    if (*str == (char)c) {
      last = str;
    }
    str++;
  }
  if ((char)c == '\0') {
    last = str;
  }
  return (char*)last;
}

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t i = 0;
  while (str1[i] != '\0') {
    s21_size_t j = 0;
    while (str2[j] != '\0') {
      if (str1[i] == str2[j]) {
        return i;
      }
      j++;
    }
    i++;
  }
  return i;
}

char* s21_strpbrk(const char* str1, const char* str2) {
  while (*str1 != '\0') {
    const char* s2 = str2;
    while (*s2 != '\0') {
      if (*str1 == *s2) {
        return (char*)str1;
      }
      s2++;
    }
    str1++;
  }
  return S21_NULL;
}

char* s21_strstr(const char* haystack, const char* needle) {
  if (*needle == '\0') {
    return (char*)haystack;
  }
  while (*haystack != '\0') {
    const char* h = haystack;
    const char* n = needle;
    while (*h != '\0' && *n != '\0' && *h == *n) {
      h++;
      n++;
    }
    if (*n == '\0') {
      return (char*)haystack;
    }
    haystack++;
  }
  return S21_NULL;
}

char* s21_strtok(char* str, const char* delim) {
  static char* last = S21_NULL;
  if (str != S21_NULL) {
    last = str;
  }
  if (last == S21_NULL) {
    return S21_NULL;
  }
  while (*last != '\0' && s21_strchr(delim, *last) != S21_NULL) {
    last++;
  }
  if (*last == '\0') {
    last = S21_NULL;
    return S21_NULL;
  }
  char* token_start = last;
  while (*last != '\0' && s21_strchr(delim, *last) == S21_NULL) {
    last++;
  }
  if (*last != '\0') {
    *last = '\0';
    last++;
  } else {
    last = S21_NULL;
  }
  return token_start;
}