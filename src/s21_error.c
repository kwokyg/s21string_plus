#include "s21_error.h"

#include "s21_string.h"

char* s21_strerror(int errnum) {
  static char buffer[128];

  if (errnum >= 0 && errnum < NUMBER_OF_ERRORS) {
    return s21_error_array[errnum];
  } else {
    char* p = buffer;
    const char* src = UNKNOWN;

    while (*src != '\0' && (p - buffer) < (int)(sizeof(buffer) - 20)) {
      *p++ = *src++;
    }

#if defined(__APPLE__) || defined(__MACH__)
    if (*(p - 1) != ' ') {
      *p++ = ' ';
    }
#else
    *p++ = ' ';
#endif
    int temp_err = errnum;
    char digits[32];
    int i = 0;
    int is_negative = 0;

    if (temp_err < 0) {
      is_negative = 1;
      temp_err = -temp_err;
    }

    if (temp_err == 0) {
      digits[i++] = '0';
    } else {
      while (temp_err > 0 && i < (int)sizeof(digits)) {
        digits[i++] = (char)('0' + (temp_err % 10));
        temp_err /= 10;
      }
    }

    if (is_negative && (p - buffer) < (int)(sizeof(buffer) - 2)) {
      *p++ = '-';
    }

    while (i > 0 && (p - buffer) < (int)(sizeof(buffer) - 1)) {
      *p++ = digits[--i];
    }

    *p = '\0';
    return buffer;
  }
}