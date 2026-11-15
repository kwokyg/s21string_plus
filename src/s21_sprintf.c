#include "s21_sprintf.h"

int s21_sprintf(char* str, const char* format, ...) {
  if (str == S21_NULL || format == S21_NULL) {
    return -1;
  }
  va_list args;
  va_start(args, format);
  s21_size_t idx = 0;

  while (*format != '\0') {
    if (*format != '%') {
      str[idx++] = *format++;
    } else {
      format++;
      FormatSpec spec = {0};
      format = parse_specifier(format, &spec);
      process_specifier(str, &idx, spec, &args);
    }
  }
  str[idx] = '\0';
  va_end(args);
  return (int)idx;
}

const char* parse_specifier(const char* format, FormatSpec* spec) {
  while (*format == '-' || *format == '+' || *format == ' ') {
    if (*format == '-') spec->minus = 1;
    if (*format == '+') spec->plus = 1;
    if (*format == ' ') spec->space = 1;
    format++;
  }
  while (*format >= '0' && *format <= '9') {
    spec->width = spec->width * 10 + (*format++ - '0');
  }
  if (*format == '.') {
    spec->has_precision = 1;
    format++;
    while (*format >= '0' && *format <= '9') {
      spec->precision = spec->precision * 10 + (*format++ - '0');
    }
  }
  if (*format == 'h' || *format == 'l') {
    spec->length = *format++;
  }
  if (*format != '\0') {
    spec->specifier = *format++;
  }
  return format;
}

void process_specifier(char* str, s21_size_t* idx, FormatSpec spec,
                       va_list* args) {
  if (spec.specifier == 'c') {
    char ch = (char)va_arg(*args, int);
    process_char(str, idx, spec, ch);
  } else if (spec.specifier == '%') {
    spec.minus = 0;
    spec.width = 0;
    process_char(str, idx, spec, '%');
  } else if (spec.specifier == 's') {
    const char* s = va_arg(*args, const char*);
    process_string(str, idx, spec, s);
  } else if (spec.specifier == 'd') {
    process_int(str, idx, spec, args);
  } else if (spec.specifier == 'u') {
    process_uint(str, idx, spec, args);
  } else if (spec.specifier == 'f') {
    process_float(str, idx, spec, args);
  }
}

void process_char(char* str, s21_size_t* idx, FormatSpec spec, char ch) {
  int pad = (spec.width > 1) ? spec.width - 1 : 0;
  if (!spec.minus) {
    for (int i = 0; i < pad; i++) {
      str[(*idx)++] = ' ';
    }
  }
  str[(*idx)++] = ch;
  if (spec.minus) {
    for (int i = 0; i < pad; i++) {
      str[(*idx)++] = ' ';
    }
  }
}

void process_string(char* str, s21_size_t* idx, FormatSpec spec,
                    const char* s) {
  const char* src = (s == S21_NULL) ? "(null)" : s;
  s21_size_t len = s21_strlen(src);
  if (spec.has_precision && (s21_size_t)spec.precision < len) {
    len = (s21_size_t)spec.precision;
  }
  int pad = (spec.width > (int)len) ? spec.width - (int)len : 0;
  if (!spec.minus) {
    for (int i = 0; i < pad; i++) str[(*idx)++] = ' ';
  }
  for (s21_size_t i = 0; i < len; i++) {
    str[(*idx)++] = src[i];
  }
  if (spec.minus) {
    for (int i = 0; i < pad; i++) str[(*idx)++] = ' ';
  }
}

void process_int(char* str, s21_size_t* idx, FormatSpec spec, va_list* args) {
  long long val = 0;
  if (spec.length == 'l') {
    val = va_arg(*args, long int);
  } else if (spec.length == 'h') {
    val = (short int)va_arg(*args, int);
  } else {
    val = va_arg(*args, int);
  }
  int is_neg = (val < 0);
  unsigned long long uval = is_neg ? (unsigned long long)(-(val + 1)) + 1ULL
                                   : (unsigned long long)val;
  char digits[32] = {0};
  if (!(spec.has_precision && spec.precision == 0 && uval == 0)) {
    ull_to_str(uval, digits);
  }
  format_number_buffer(str, idx, spec, digits, is_neg);
}

void process_uint(char* str, s21_size_t* idx, FormatSpec spec, va_list* args) {
  unsigned long long uval = 0;
  if (spec.length == 'l') {
    uval = va_arg(*args, unsigned long int);
  } else if (spec.length == 'h') {
    uval = (unsigned short int)va_arg(*args, unsigned int);
  } else {
    uval = va_arg(*args, unsigned int);
  }
  spec.plus = 0;
  spec.space = 0;
  char digits[32] = {0};
  if (!(spec.has_precision && spec.precision == 0 && uval == 0)) {
    ull_to_str(uval, digits);
  }
  format_number_buffer(str, idx, spec, digits, 0);
}

static void build_float_digits(double val, int prec, char* out) {
  double p10 = pow(10.0, prec);
  double rounded = round(val * p10);
  unsigned long long whole = (unsigned long long)(rounded / p10);
  unsigned long long frac = (unsigned long long)fmod(rounded, p10);
  char w_buf[32] = {0};
  ull_to_str(whole, w_buf);
  s21_size_t pos = 0;
  for (s21_size_t i = 0; w_buf[i] != '\0'; i++) out[pos++] = w_buf[i];
  if (prec > 0) {
    out[pos++] = '.';
    char f_buf[32] = {0};
    ull_to_str(frac, f_buf);
    int flen = (int)s21_strlen(f_buf);
    for (int i = 0; i < prec - flen; i++) out[pos++] = '0';
    for (int i = 0; f_buf[i] != '\0'; i++) out[pos++] = f_buf[i];
  }
  out[pos] = '\0';
}

void process_float(char* str, s21_size_t* idx, FormatSpec spec, va_list* args) {
  double val = va_arg(*args, double);
  int prec = spec.has_precision ? spec.precision : 6;
  int is_neg = signbit(val) ? 1 : 0;
  if (is_neg) val = -val;
  char num_buf[64] = {0};
  build_float_digits(val, prec, num_buf);
  spec.has_precision = 0;
  spec.precision = 0;
  format_number_buffer(str, idx, spec, num_buf, is_neg);
}

void format_number_buffer(char* str, s21_size_t* idx, FormatSpec spec,
                          const char* digits, int is_neg) {
  int dlen = (int)s21_strlen(digits);
  int zeros = (spec.precision > dlen) ? spec.precision - dlen : 0;
  char sign = is_neg ? '-' : (spec.plus ? '+' : (spec.space ? ' ' : '\0'));
  int total = dlen + zeros + (sign != '\0' ? 1 : 0);
  int pad = (spec.width > total) ? spec.width - total : 0;

  if (!spec.minus) {
    for (int i = 0; i < pad; i++) str[(*idx)++] = ' ';
  }
  if (sign != '\0') str[(*idx)++] = sign;
  for (int i = 0; i < zeros; i++) str[(*idx)++] = '0';
  for (int i = 0; i < dlen; i++) str[(*idx)++] = digits[i];
  if (spec.minus) {
    for (int i = 0; i < pad; i++) str[(*idx)++] = ' ';
  }
}

void ull_to_str(unsigned long long val, char* buf) {
  s21_size_t i = 0;
  if (val == 0) {
    buf[i++] = '0';
  }
  while (val > 0) {
    buf[i++] = (char)((val % 10ULL) + '0');
    val /= 10ULL;
  }
  buf[i] = '\0';
  reverse_str(buf, i);
}

void reverse_str(char* buf, s21_size_t len) {
  for (s21_size_t i = 0; i < len / 2; i++) {
    char tmp = buf[i];
    buf[i] = buf[len - 1 - i];
    buf[len - 1 - i] = tmp;
  }
}