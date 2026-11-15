#include "s21_string.h"

s21_size_t s21_strlen(const char* str) {
  const char* s = str;
  while (*s != '\0') {
    s++;
  }
  return (s - str);
}

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  char* s = dest;
  while (*s != '\0') {
    s++;
  }
  s21_size_t i = 0;
  while (i < n && src[i] != '\0') {
    s[i] = src[i];
    i++;
  }
  s[i] = '\0';
  return dest;
}

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  s21_size_t i = 0;
  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  while (i < n) {
    dest[i] = '\0';
    i++;
  }
  return dest;
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  s21_size_t i = 0;
  while (i < n && str1[i] != '\0' && str2[i] == str1[i]) {
    i++;
  }
  if (i == n) {
    return 0;
  }
  return (unsigned char)str1[i] - (unsigned char)str2[i];
}