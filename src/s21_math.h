#ifndef S21_MATH_H
#define S21_MATH_H

#define PI \
  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#define APPR 2000

long double factorial(unsigned int num);
long double custom_int_power(double x, int exp);
long double get_inf();
long double get_nan();

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

#endif /* S21_MATH_H */
