#include "s21_math.h"

long double factorial(unsigned int num) {
  long double result = 1;
  for (unsigned int i = 1; i <= num; i++) result *= i;
  return result;
}

long double custom_int_power(double x, int exp) {
  long double result = 1;
  if (exp >= 0)
    for (int i = 0; i < exp; i++) result *= x;
  else
    for (int i = 0; i > exp; i--) result /= x;

  return result;
}

long double get_inf() { return 1.0 / 0.0; }
long double get_nan() { return 0.0 / 0.0; }

int s21_abs(int x) {
  if (x < 0) x = -x;
  return x;
}

long double s21_acos(double x) {
  long double result = 0;
  if (x > -1 && x < 1) {
    result = PI / 2;
    long double sum = 0;
    int appr = 800;
    for (int i = 0; i < appr; i++)
      sum += factorial(2 * i * 1.0) * custom_int_power(x, 2 * i + 1) /
             ((2 * i + 1) * custom_int_power(2, 2 * i) * factorial(i) *
              factorial(i));

    result -= sum;
  } else if (x == 1)
    result = 0;
  else if (x == -1)
    result = PI;
  else
    result = get_nan();

  return result;
}

long double s21_asin(double x) {
  long double result = 0;
  if (s21_fabs(x) <= 1)
    result = PI / 2 - s21_acos(x);
  else
    result = get_nan();
  return result;
}

long double s21_atan(double x) {
  long double result = 0;
  if (x <= 1 && x >= -1) {
    int appr = 800;
    for (int i = 0; i < appr; i++) {
      if (i % 2 == 0)
        result += custom_int_power(x, 2 * i + 1) / (2 * i + 1);
      else
        result += -custom_int_power(x, 2 * i + 1) / (2 * i + 1);
    }
  } else if (x > 1)
    result = PI / 2 - s21_atan(1 / x);
  else if (x < 1)
    result = -PI / 2 - s21_atan(1 / x);

  return result;
}

long double s21_ceil(double x) {
  long double result = 0.0;

  if (x >= 0) {
    result = (long)x;
    if (x != (long)x) result += 1.0;
  } else
    result = (long)x;

  return result;
}

long double s21_cos(double x) {
  while (x > 2 * PI) x -= 2 * PI;
  while (x < -2 * PI) x += 2 * PI;
  long double result = 0;
  for (int i = 0; i < APPR; i++) {
    if (i % 2 == 0)
      result += custom_int_power(x, 2 * i) / factorial(2 * i);
    else
      result += -custom_int_power(x, 2 * i) / factorial(2 * i);
  }

  return result;
}

long double s21_exp(double x) {
  int is_neg = 0;
  if (x < 0) {
    is_neg = 1;
    x = -x;
  }
  long double result = 0;
  for (int i = 0; i < APPR; i++)
    result += custom_int_power(x, i) / factorial(i);

  if (is_neg) result = 1 / result;

  return result;
}

long double s21_fabs(double x) {
  if (x < 0) x = -x;
  return x;
}

long double s21_floor(double x) {
  long double result = 0;
  if (x >= 0.0)
    result = (long double)((long long)x);
  else {
    long double intPart = (long double)((long long)x);
    if (intPart == x)
      result = intPart;
    else
      result = intPart - 1.0;
  }
  return result;
}

long double s21_fmod(double x, double y) {
  if (y == 0) return get_nan();

  double quotient = x / y;
  long long int_part = (long long)quotient;
  return x - y * (long double)int_part;
}

long double s21_log(double x) {
  if (x < 0)
    return get_nan();
  else if (x == 0)
    return -get_inf();

  long double epsilon = 1e-8;
  long double guess = x - 1.0;
  long double ln_x = 0.0;

  while (s21_fabs(x - s21_exp(ln_x)) > epsilon) {
    ln_x = guess + (x - s21_exp(guess)) / s21_exp(guess);
    guess = ln_x;
  }

  return ln_x;
}

long double s21_pow(double base, double exp) {
  if ((int)exp == exp)
    return custom_int_power(base, exp);
  else if (base < 0)
    return get_nan();

  long double result = 0;
  if (base < 0) base = -base;

  result = s21_exp(exp * s21_log(base));

  return result;
}

long double s21_sin(double x) {
  while (x > 2 * PI) x -= 2 * PI;
  while (x < -2 * PI) x += 2 * PI;
  long double result = 0;
  for (int i = 1; i < APPR; i++) {
    if (i % 2 == 1)
      result += custom_int_power(x, 2 * i - 1) / factorial(2 * i - 1);
    else
      result += -custom_int_power(x, 2 * i - 1) / factorial(2 * i - 1);
  }

  return result;
}

long double s21_sqrt(double x) {
  long double result = s21_pow(x, 0.5);
  if (x < 0) result = get_nan();
  if (x == 0) result = 0;
  return result;
}

long double s21_tan(double x) {
  long double result = 0;

  result = s21_sin(x) / s21_cos(x);

  return result;
}
