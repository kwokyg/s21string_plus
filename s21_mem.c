#include "s21_string.h"

void* s21_memchr(const void* str, int c,
                 s21_size_t n)  // ищет первое вхождение символа c (как unsigned
                                // char) в первых n байтах памяти str.
{
  void* res = S21_NULL;
  if (str != S21_NULL) {
    const unsigned char* p = (const unsigned char*)str;
    unsigned char t = (unsigned char)c;
    for (s21_size_t i = 0; res == S21_NULL && i < n; i++) {
      if (p[i] == t) {
        res = (void*)(p + i);
      }
    }
  }
  return res;
}

int s21_memcmp(const void* str1, const void* str2,
               s21_size_t n)  // побайтово сравнивает первые n байтов блоков
                              // памяти str1 и str2.
{
  int res = 0;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    const unsigned char* r1 = (const unsigned char*)str1;
    const unsigned char* r2 = (const unsigned char*)str2;
    for (s21_size_t i = 0; res == 0 && i < n; i++) {
      if (r1[i] != r2[i]) {
        res = (int)r1[i] - (int)r2[i];
      }
    }
  }
  return res;
}

void* s21_memcpy(
    void* dest, const void* src,
    s21_size_t n)  // копирует n байт из области памяти src в область dest.
{
  if (dest != S21_NULL && src != S21_NULL) {
    unsigned char* copy = (unsigned char*)dest;
    const unsigned char* read = (const unsigned char*)src;
    for (s21_size_t i = 0; i < n; i++) {
      copy[i] = read[i];
    }
  }
  return dest;
}

void* s21_memset(
    void* str, int c,
    s21_size_t n) {  // заполняет первые n байтов области str значением байта c
  if (str != S21_NULL) {
    unsigned char* p = (unsigned char*)str;
    for (s21_size_t i = 0; i < n; i++) {
      p[i] = (unsigned char)c;
    }
  }
  return str;
}