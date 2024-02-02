#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"

#define EPSILON 1E-6
#define FUNC_QUANT 19

#define DOUBLE_X_LDOUBLE_Y \
  double x = (double)_i;   \
  long double y = (long double)_i;

START_TEST(test_s21_factorial_of_0) {
  unsigned int num = 0;
  long double result = factorial(num);
  ck_assert_msg(result == 1.0L, "Factorial of 0 should be 1");
}
END_TEST

START_TEST(test_s21_factorial_of_5) {
  unsigned int num = 5;
  long double result = factorial(num);
  ck_assert_msg(result == 120.0L, "Factorial of 5 should be 120");
}
END_TEST

START_TEST(test_s21_factorial_of_20) {
  unsigned int num = 20;
  long double result = factorial(num);
  ck_assert_msg(result == 2432902008176640000.0L,
                "Factorial of 10 should be 2432902008176640000.0");
}
END_TEST

Suite *s21_factorial_suite(void) {
  Suite *s = suite_create("s21_factorial");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_factorial_of_0);
  tcase_add_test(tc_core, test_s21_factorial_of_5);
  tcase_add_test(tc_core, test_s21_factorial_of_20);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_positive_integer) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(custom_int_power(x, x), powl(y, y), EPSILON);
}
END_TEST

START_TEST(test_zero_exponent) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(custom_int_power(x, 0), powl(y, 0), EPSILON);
}
END_TEST

START_TEST(test_negative_integer) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(custom_int_power(x, x), powl(y, y), EPSILON);
}
END_TEST

Suite *s21_custom_int_power_suite(void) {
  Suite *s = suite_create("s21_custom_int_power");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_positive_integer, 1, 144);
  tcase_add_loop_test(tc_core, test_zero_exponent, -144.0, 144.0);
  tcase_add_loop_test(tc_core, test_negative_integer, -144, -1);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_get_inf_positive) {
  long double result = get_inf();
  ck_assert_msg(isinf(result) && result > 0,
                "get_inf() should return positive infinity");
}
END_TEST

START_TEST(test_get_inf_not_nan) {
  long double result = get_inf();
  ck_assert_msg(!isnan(result), "get_inf() should not return NaN");
}
END_TEST

Suite *s21_get_inf_suite(void) {
  Suite *s = suite_create("s21_get_inf");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_get_inf_positive);
  tcase_add_test(tc_core, test_get_inf_not_nan);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_get_nan_is_nan) {
  long double result = get_nan();
  ck_assert(isnan(result));
}
END_TEST

START_TEST(test_get_nan_is_not_finite) {
  long double result = get_nan();
  ck_assert(!isfinite(result));
}
END_TEST

START_TEST(test_get_nan_is_not_normal) {
  long double result = get_nan();
  ck_assert(!isnormal(result));
}
END_TEST

Suite *s21_get_nan_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_get_nan");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_get_nan_is_nan);
  tcase_add_test(tc_core, test_get_nan_is_not_finite);
  tcase_add_test(tc_core, test_get_nan_is_not_normal);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_abs) { ck_assert_int_eq(s21_abs(_i), abs(_i)); }
END_TEST;

START_TEST(test_s21_abs_invalid_input) {
  ck_assert_int_eq(s21_abs('a'), abs('a'));
}
END_TEST;

Suite *s21_abs_suite(void) {
  Suite *s = suite_create("s21_abs");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_s21_abs, -200, 10);
  tcase_add_test(tc_core, test_s21_abs_invalid_input);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_acos_valid_input) {
  DOUBLE_X_LDOUBLE_Y
  x *= 0.01;
  y *= 0.01L;
  ck_assert_double_eq_tol(s21_acos(x), acosl(y), EPSILON);
}
END_TEST

START_TEST(test_s21_acos_one) {
  ck_assert_double_eq_tol(s21_acos(-1), acosl(-1), EPSILON);
  ck_assert_double_eq_tol(s21_acos(1), acosl(1), EPSILON);
}
END_TEST

START_TEST(test_s21_acos_nan) {
  ck_assert(isnan(s21_acos(-10)) && isnan(acosl(-10)));
}
END_TEST

Suite *s21_acos_suite(void) {
  Suite *s = suite_create("s21_acos");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_s21_acos_valid_input, -99, 99);
  tcase_add_test(tc_core, test_s21_acos_one);
  tcase_add_test(tc_core, test_s21_acos_nan);
  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_asin_within_range) {
  DOUBLE_X_LDOUBLE_Y
  x *= 0.01;
  y *= 0.01L;
  ck_assert_double_eq_tol(s21_asin(x), asinl(y), EPSILON);
}
END_TEST

START_TEST(test_s21_asin_outside_range_positive) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert(isnan(s21_asin(x)) && isnan(asinl(y)));
}
END_TEST

START_TEST(test_s21_asin_outside_range_negative) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert(isnan(s21_asin(x)) && isnan(asinl(y)));
}
END_TEST

Suite *s21_asin_suite(void) {
  Suite *s = suite_create("s21_asin");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_s21_asin_within_range, -99, 99);
  tcase_add_loop_test(tc_core, test_s21_asin_outside_range_positive, 2, 30);
  tcase_add_loop_test(tc_core, test_s21_asin_outside_range_negative, -30, -2);
  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_atan_positive) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_atan(x), atanl(y), EPSILON);
}

START_TEST(test_s21_atan_negative) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_atan(x), atanl(y), EPSILON);
}
END_TEST

Suite *s21_atan_suite(void) {
  Suite *s = suite_create("s21_atan");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_s21_atan_positive, 2, 100);
  tcase_add_loop_test(tc_core, test_s21_atan_negative, -100, -2);

  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_s21_ceil_positive) {
  DOUBLE_X_LDOUBLE_Y
  x *= 0.01;
  y *= 0.01L;
  ck_assert_double_eq_tol(s21_ceil(x), ceill(y), EPSILON);
}

START_TEST(test_s21_ceil_negative) {
  DOUBLE_X_LDOUBLE_Y
  x *= 0.01;
  y *= 0.01L;
  ck_assert_double_eq_tol(s21_ceil(x), ceill(y), EPSILON);
}

START_TEST(test_s21_ceil_zero) {
  ck_assert_double_eq_tol(s21_ceil(0), ceill(0), EPSILON);
}

Suite *s21_ceil_suite(void) {
  Suite *s = suite_create("s21_ceil");
  TCase *tc = tcase_create("s21_ceil_test");

  tcase_add_loop_test(tc, test_s21_ceil_positive, 0, 300);
  tcase_add_loop_test(tc, test_s21_ceil_negative, -300, 0);
  tcase_add_test(tc, test_s21_ceil_zero);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_s21_cos_zero) {
  double x = 0.0;
  long double result = s21_cos(x);
  long double expected = cosl(x);

  ck_assert_double_eq_tol(result, expected, EPSILON);
}

START_TEST(test_s21_cos_positive) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_cos(x), cos(y), EPSILON);
}

START_TEST(test_s21_cos_negative) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_cos(x), cos(y), EPSILON);
}

Suite *s21_cos_suite(void) {
  Suite *s = suite_create("s21_cos");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_s21_cos_zero);
  tcase_add_loop_test(tc_core, test_s21_cos_positive, 1, 100);
  tcase_add_loop_test(tc_core, test_s21_cos_negative, -100, -1);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_exp_zero) {
  double x = 0.0;
  long double result = s21_exp(x);
  long double expected = expl(x);
  ck_assert_double_eq_tol(result, expected, EPSILON);
}
END_TEST

START_TEST(test_s21_exp_positive) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_exp(x), expl(y), EPSILON);
}
END_TEST

Suite *s21_exp_suite(void) {
  Suite *s = suite_create("s21_exp");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_exp_zero);
  tcase_add_loop_test(tc_core, test_s21_exp_positive, 0, 20);

  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_s21_fabs_positive) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_fabs(x), fabsl(y), EPSILON);
}
END_TEST

START_TEST(test_s21_fabs_negative) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_fabs(x), fabsl(y), EPSILON);
}
END_TEST

START_TEST(test_s21_fabs_zero) {
  long double result = s21_fabs(0.0);
  long double expected = fabsl(0.0);
  ck_assert_double_eq_tol(result, expected, EPSILON);
}
END_TEST

Suite *s21_fabs_suite(void) {
  Suite *s = suite_create("s21_fabs");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_s21_fabs_positive, 0, 300);
  tcase_add_loop_test(tc_core, test_s21_fabs_negative, -300, 0);
  tcase_add_test(tc_core, test_s21_fabs_zero);

  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_s21_floor_positive) {
  DOUBLE_X_LDOUBLE_Y
  x *= 0.01;
  y *= 0.01L;
  ck_assert_double_eq_tol(s21_floor(x), floorl(y), EPSILON);
}
END_TEST

START_TEST(test_s21_floor_negative) {
  DOUBLE_X_LDOUBLE_Y
  x *= 0.01;
  y *= 0.01L;
  ck_assert_double_eq_tol(s21_floor(x), floorl(y), EPSILON);
}
END_TEST

Suite *s21_floor_suite(void) {
  Suite *s = suite_create("s21_floor");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_s21_floor_positive, 0, 300);
  tcase_add_loop_test(tc_core, test_s21_floor_negative, -300, 0);

  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_s21_fmod_positive_x_and_positive_y) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_fmod(x + 3.2, x), fmodl(y + 3.2L, y), EPSILON);
}
END_TEST

START_TEST(test_s21_fmod_negative_x_and_positive_y) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_fmod(-x - 3.1, x), fmodl(-y - 3.1L, y), EPSILON);
}
END_TEST

START_TEST(test_s21_fmod_positive_x_and_negative_y) {
  DOUBLE_X_LDOUBLE_Y

  ck_assert_double_eq_tol(s21_fmod(x + 5.32, -x), fmodl(y + 5.32L, -y),
                          EPSILON);
}
END_TEST

START_TEST(test_s21_fmod_equal_values) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_fmod(x, x), fmodl(y, y), EPSILON);
}
END_TEST

START_TEST(test_s21_fmod_get_nan) {
  double x = 10.0;
  double y = 0;
  double result = s21_fmod(x, y);
  double expected = fmodl(x, y);
  ck_assert(isnan(result) && isnan(expected));
}
END_TEST

Suite *s21_fmod_suite(void) {
  Suite *s = suite_create("s21_fmod");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_s21_fmod_positive_x_and_positive_y, 1, 100);
  tcase_add_loop_test(tc_core, test_s21_fmod_negative_x_and_positive_y, 1, 100);
  tcase_add_loop_test(tc_core, test_s21_fmod_positive_x_and_negative_y, 1, 100);
  tcase_add_loop_test(tc_core, test_s21_fmod_equal_values, 1, 30);
  tcase_add_test(tc_core, test_s21_fmod_get_nan);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_log_with_zero_input) {
  double x = 0.0;
  long double result = s21_log(x);
  ck_assert(isinf(result));
}
END_TEST

START_TEST(test_s21_log_with_negative_input) {
  long double result = s21_log(_i);
  ck_assert(isnan(result));
}
END_TEST

START_TEST(test_s21_log_with_positive_input) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_log(x), logl(y), EPSILON);
}
END_TEST

Suite *s21_log_suite(void) {
  Suite *s = suite_create("s21_log");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_log_with_zero_input);
  tcase_add_loop_test(tc_core, test_s21_log_with_negative_input, -30, -1);
  tcase_add_loop_test(tc_core, test_s21_log_with_positive_input, 1, 30);
  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_pow_with_positive_values) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_pow(x, x), powl(y, y), EPSILON);
}
END_TEST

START_TEST(test_s21_pow_with_negative_base) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_pow(-x, x), powl(-y, y), EPSILON);
}
END_TEST

START_TEST(test_s21_pow_with_negative_exp) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_pow(x, -x), powl(y, -y), EPSILON);
}
END_TEST

START_TEST(test_s21_pow_with_fractional_exp) {
  DOUBLE_X_LDOUBLE_Y
  double base = 10;

  if ((_i % 2) != 0) {
    x = x / 2.0;
    y = y / 2.0L;
  } else {
    x = x / 2.0 + 0.3334;
    y = y / 2.0L + 0.3334L;
  }

  ck_assert_double_eq_tol(s21_pow(base, x), powl(base, y), EPSILON);
}
END_TEST

Suite *s21_pow_suite(void) {
  Suite *s = suite_create("s21_pow");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_s21_pow_with_positive_values, 1, 144);
  tcase_add_loop_test(tc_core, test_s21_pow_with_negative_base, 1, 144);
  tcase_add_loop_test(tc_core, test_s21_pow_with_negative_exp, 1, 144);
  tcase_add_loop_test(tc_core, test_s21_pow_with_fractional_exp, 1, 10);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_sin_zero) {
  double x = 0;
  long double expected = sinl(x);
  long double result = s21_sin(x);
  ck_assert_double_eq_tol(result, expected, EPSILON);
}
END_TEST

START_TEST(test_s21_sin_positive) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_sin(x), sinl(y), EPSILON);
}
END_TEST

START_TEST(test_s21_sin_negative) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_sin(x), sinl(y), EPSILON);
}
END_TEST

Suite *s21_sin_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sin");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sin_zero);
  tcase_add_loop_test(tc_core, test_s21_sin_positive, 1, 100);
  tcase_add_loop_test(tc_core, test_s21_sin_negative, -100, -1);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_sqrt_positive) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_sqrt(x), sqrtl(y), EPSILON);
}
END_TEST

START_TEST(test_s21_sqrt_zero) {
  double x = 0.0;
  ck_assert_double_eq_tol(s21_sqrt(x), sqrtl(x), EPSILON);
}
END_TEST

START_TEST(test_s21_sqrt_negative) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert(isnan(s21_sqrt(x)) && isnan(sqrtl(y)));
}
END_TEST

Suite *s21_sqrt_suite(void) {
  Suite *s = suite_create("s21_sqrt");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_s21_sqrt_positive, 1, 10);
  tcase_add_loop_test(tc_core, test_s21_sqrt_negative, -10, -1);
  tcase_add_test(tc_core, test_s21_sqrt_zero);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_tan_positive) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_tan(x), tanl(y), EPSILON);
}
END_TEST

START_TEST(test_s21_tan_negative) {
  DOUBLE_X_LDOUBLE_Y
  ck_assert_double_eq_tol(s21_tan(x), tanl(y), EPSILON);
}
END_TEST

START_TEST(test_s21_tan_boundary_case) {
  double x = 1.57079;
  long double expected = tanl(x);
  long double result = s21_tan(x);
  ck_assert_double_eq_tol(result, expected, EPSILON);
}
END_TEST

Suite *s21_tan_suite(void) {
  Suite *s = suite_create("s21_tan");
  TCase *tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_s21_tan_positive, 1, 20);
  tcase_add_loop_test(tc_core, test_s21_tan_negative, -20, -1);
  tcase_add_test(tc_core, test_s21_tan_boundary_case);
  suite_add_tcase(s, tc_core);

  return s;
}

int run_test_case(Suite *(*func)(void)) {
  Suite *s;
  SRunner *sr;
  int number_failed = 0;

  s = func();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}

int main(void) {
  Suite *(*suites[FUNC_QUANT])(void) = {
      s21_factorial_suite, s21_custom_int_power_suite,
      s21_get_inf_suite,   s21_get_nan_suite,
      s21_abs_suite,       s21_acos_suite,
      s21_asin_suite,      s21_atan_suite,
      s21_ceil_suite,      s21_cos_suite,
      s21_exp_suite,       s21_fabs_suite,
      s21_floor_suite,     s21_fmod_suite,
      s21_log_suite,       s21_pow_suite,
      s21_sin_suite,       s21_sqrt_suite,
      s21_tan_suite};

  for (int i = 0; i < FUNC_QUANT; i++) {
    run_test_case(suites[i]);
  }

  return 0;
}
