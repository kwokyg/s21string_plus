#ifndef S21_SPRINTF_H_
#define S21_SPRINTF_H_

#include <math.h>
#include <stdarg.h>

#include "s21_string.h"

typedef struct {
  int minus;
  int plus;
  int space;
  int width;
  int precision;
  int has_precision;
  char length;
  char specifier;
} FormatSpec;

const char* parse_specifier(const char* format, FormatSpec* spec);
void process_specifier(char* str, s21_size_t* idx, FormatSpec spec,
                       va_list* args);
void process_char(char* str, s21_size_t* idx, FormatSpec spec, char ch);
void process_string(char* str, s21_size_t* idx, FormatSpec spec, const char* s);
void process_int(char* str, s21_size_t* idx, FormatSpec spec, va_list* args);
void process_uint(char* str, s21_size_t* idx, FormatSpec spec, va_list* args);
void process_float(char* str, s21_size_t* idx, FormatSpec spec, va_list* args);
void format_number_buffer(char* str, s21_size_t* idx, FormatSpec spec,
                          const char* digits, int is_neg);
void ull_to_str(unsigned long long val, char* buf);
void reverse_str(char* buf, s21_size_t len);

#endif