#include <check.h>

#include "smart_calc_v1/back/s21_calc.h"

START_TEST(test_empty_input_1) {
  char *str = "        ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, EMPTY_INPUT);
}
END_TEST

START_TEST(test_empty_input_2) {
  char *str = "";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, EMPTY_INPUT);
}
END_TEST

START_TEST(test_invalid_value_1) {
  char *str = "6 + son(pi)";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_invalid_value_2) {
  char *str = "  ~8.874 + tan(0)  ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_invalid_value_3) {
  char *str = "164.4.5 - sqrt(144)";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_invalid_value_4) {
  char *str = " 6E+1E8 + 5  mod 2 ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_invalid_value_5) {
  char *str = "-785/ 2^9 + y";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_invalid_value_6) {
  char *str = "(uau - 98 * 252)";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_invalid_value_7) {
  char *str = "  6.4 + cos(l)  ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_invalid_value_8) {
  char *str = "   25 + E-2  ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_simple_case_1) {
  char *str = "3+(5-2*3^2)";
  double answer = 3 + (5 - 2 * pow(3, 2));
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_2) {
  char *str = "3 / (5-5)";
  double answer = 3. / (5. - 5.);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq(result, answer);
}
END_TEST

START_TEST(test_simple_case_3) {
  char *str = "3/5-5^ 2*3.25";
  double answer = 3. / 5 - powl(5, 2) * 3.25;
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_4) {
  char *str = "sin(pi)";
  double answer = sin(M_PI);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_5) {
  char *str = "ln(e)";
  double answer = log(M_E);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_6) {
  char *str = " 10 - 5 mod 3";
  double answer = 10 - fmod(5, 3);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_7) {
  char *str = "tan(0.8)";
  double answer = tan(0.8);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_8) {
  char *str = "log(1000)";
  double answer = log10(1000);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_9) {
  char *str = "-cos(0)";
  double answer = -cos(0);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_10) {
  char *str = "sqrt(144)";
  double answer = sqrt(144);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_11) {
  char *str = "asin(0.42)";
  double answer = asin(0.42);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_12) {
  char *str = "acos(0.542)";
  double answer = acos(0.542);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_13) {
  char *str = "atan(0.21)";
  double answer = atan(0.21);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_14) {
  char *str = "-(-cos(pi) ^ 5) ";
  double answer = -pow((-cos(M_PI)), 5);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_15) {
  char *str = "-(+(-(+21)))";
  double answer = 21;
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_16) {
  char *str = "(13.5) ^ (-2)";
  double answer = pow(13.5, (-2));
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_simple_case_17) {
  char *str = "  42.21 ";
  double answer = 42.21;
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_calculation_error_1) {
  char *str = "  /  ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_2) {
  char *str = " 3 *  ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_3) {
  char *str = "  +  ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_4) {
  char *str = "  +-+-+-++ 42  ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_5) {
  char *str = "  +  ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_6) {
  char *str = "(5)+(3";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_7) {
  char *str = "(5))";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_8) {
  char *str = "sin(+)";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_9) {
  char *str = "(3+5)-7)*sin(2)";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_10) {
  char *str = "(())";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_11) {
  char *str = "(.)(.)";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_12) {
  char *str = "/(sin(4))";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_13) {
  char *str = "3/ *(sin(pi))";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_14) {
  char *str = "2+4*()-sin(12)";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_15) {
  char *str = "(-1 (2 +(3 ((4) + 5)))";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_16) {
  char *str = "2 * (2 + 2))";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_17) {
  char *str = "(2) * 2 + 6 / (2.3";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_calculation_error_18) {
  char *str = "3 - sin((12)";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_hard_case_1) {
  char *str = "((2 - (1 - 2)) - 2)";
  double answer = ((2 - (1 - 2)) - 2);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_hard_case_2) {
  char *str = "sin(3) * cos(5) + 7*tan(2)";
  double answer = sin(3) * cos(5) + 7 * tan(2);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_hard_case_3) {
  char *str = "sin(4 + 5) * cos(-2) ^ (-3) - (-tan(1))";
  double answer = sin(4 + 5) * pow(cos(-2), -3) - (-tan(1));
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_hard_case_4) {
  char *str = "sin(cos(4) * (-2))^tan(12)";
  double answer = pow(sin(cos(4) * (-2)), tan(12));
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_hard_case_5) {
  char *str = "-(+sqrt(2.2 * 3 - 6)^3)";
  double answer = -(pow(+sqrt(2.2 * 3 - 6), 3));
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_hard_case_6) {
  char *str = "ln(12+213821*7)^(-2)+3";
  double answer = pow(log(12 + 213821 * 7), -2) + 3;
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_hard_case_7) {
  char *str = "5 + 3 * 2 * sqrt(3) + sqrt(53 + 55 * 4)";
  double answer = 5 + 3 * 2 * sqrt(3) + sqrt(53 + 55 * 4);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_hard_case_8) {
  char *str =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  double answer = 15.0 / (7 - (1 + 1)) * 3 -
                  (2 + (1 + 1)) * 15.0 / (7 - (200 + 1)) * 3 -
                  (2 + (1 + 1)) * (15.0 / (7 - (1 + 1)) * 3 - (2 + (1 + 1)) +
                                   15.0 / (7 - (1 + 1)) * 3 - (2 + (1 + 1)));
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_hard_case_9) {
  char *str = "3+(-4)*sin(3+5)*2/(1-5)^2^2";
  double answer = 3 + (-4) * sin(3.0 + 5) * 2.0 / pow(pow((1 - 5.0), 2.0), 2.0);
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_hard_case_10) {
  char *str = "12-32*(2143-312*(4-5)-1.32/(83.2/3))";
  double answer = 12 - 32 * (2143 - 312 * (4 - 5) - 1.32 / (83.2 / 3));
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_hard_case_11) {
  char *str = "(ln(2 * 2.71828) + log(100))/10 + 0.6";
  double answer = (log(2 * 2.71828) + log10(100)) / 10 + 0.6;
  double result = 0;
  int status = smart_calculation(str, &result, 0, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_x_case_error_1) {
  char *str = "6 + son(x)";
  double x = M_PI;
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_x_case_error_2) {
  char *str = "cos()x";
  double x = 0;
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_x_case_error_3) {
  char *str = "+3*4^(lim(x))";
  double x = 0;
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_x_case_error_4) {
  char *str = "xxx+5*2.4";
  double x = 3;
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_x_case_error_5) {
  char *str = " x / ";
  double x = 5;
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_x_case_error_6) {
  char *str = "  / x - sin(0)";
  double x = 4;
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_x_case_error_7) {
  char *str = " x - y";
  double x = 21;
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, INVALID_VALUE);
}
END_TEST

START_TEST(test_x_case_error_8) {
  char *str = " x - 42*x  ^2  ";
  double result = 0;
  int status = smart_calculation(str, &result, 0, 1);
  ck_assert_int_eq(status, INVALID_X);
}
END_TEST

START_TEST(test_x_case_1) {
  char *str = "  x*(-(1+2))^(-(x+1*(-(x+4)))) ";
  double x = 2;
  double answer = 2 * (pow(-(1 + 2), (-(2 + 1 * (-(2 + 4))))));
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_x_case_2) {
  char *str = "log(ln(x) * 12^3 - 1)";
  double x = 3223;
  double answer = log10(log(3223) * pow(12, 3) - 1);
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_x_case_3) {
  char *str = "  3+34-cos(7*x) ";
  double x = M_PI;
  double answer = 3 + 34 - cos(7 * M_PI);
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_x_case_4) {
  char *str = "  3.5-cos(x+pi/e) ";
  double x = M_PI;
  double answer = 3.5 - cos(x + M_PI / M_E);
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_x_case_5) {
  char *str = "  x + 84 / 42 mod 5 ";
  double x = 21;
  double answer = 21 + 84 / 42 % 5;
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_x_case_6) {
  char *str = "  -x + x ";
  double x = 42;
  double answer = -42 + 42;
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

START_TEST(test_x_case_7) {
  char *str = "  x / x ";
  double x = 15;
  double answer = 1;
  double result = 0;
  int status = smart_calculation(str, &result, x, 0);
  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, answer, 1E-7);
}
END_TEST

Suite *tests_empty_and_invalid(void) {
  Suite *s = suite_create("empty_and_invalid_value");
  TCase *tc1_1 = tcase_create("calc");

  tcase_add_test(tc1_1, test_empty_input_1);
  tcase_add_test(tc1_1, test_empty_input_2);

  tcase_add_test(tc1_1, test_invalid_value_1);
  tcase_add_test(tc1_1, test_invalid_value_2);
  tcase_add_test(tc1_1, test_invalid_value_3);
  tcase_add_test(tc1_1, test_invalid_value_4);
  tcase_add_test(tc1_1, test_invalid_value_5);
  tcase_add_test(tc1_1, test_invalid_value_6);
  tcase_add_test(tc1_1, test_invalid_value_7);
  tcase_add_test(tc1_1, test_invalid_value_8);

  suite_add_tcase(s, tc1_1);
  return s;
}

Suite *tests_simple(void) {
  Suite *s = suite_create("simple_case");
  TCase *tc1_1 = tcase_create("calc");

  tcase_add_test(tc1_1, test_simple_case_1);
  tcase_add_test(tc1_1, test_simple_case_2);
  tcase_add_test(tc1_1, test_simple_case_3);
  tcase_add_test(tc1_1, test_simple_case_4);
  tcase_add_test(tc1_1, test_simple_case_5);
  tcase_add_test(tc1_1, test_simple_case_6);
  tcase_add_test(tc1_1, test_simple_case_7);
  tcase_add_test(tc1_1, test_simple_case_8);
  tcase_add_test(tc1_1, test_simple_case_9);
  tcase_add_test(tc1_1, test_simple_case_10);
  tcase_add_test(tc1_1, test_simple_case_11);
  tcase_add_test(tc1_1, test_simple_case_12);
  tcase_add_test(tc1_1, test_simple_case_13);
  tcase_add_test(tc1_1, test_simple_case_14);
  tcase_add_test(tc1_1, test_simple_case_15);
  tcase_add_test(tc1_1, test_simple_case_16);
  tcase_add_test(tc1_1, test_simple_case_17);

  suite_add_tcase(s, tc1_1);
  return s;
}

Suite *tests_calculation_error(void) {
  Suite *s = suite_create("calc_error");
  TCase *tc1_1 = tcase_create("calc");

  tcase_add_test(tc1_1, test_calculation_error_1);
  tcase_add_test(tc1_1, test_calculation_error_2);
  tcase_add_test(tc1_1, test_calculation_error_3);
  tcase_add_test(tc1_1, test_calculation_error_4);
  tcase_add_test(tc1_1, test_calculation_error_5);
  tcase_add_test(tc1_1, test_calculation_error_6);

  tcase_add_test(tc1_1, test_calculation_error_7);
  tcase_add_test(tc1_1, test_calculation_error_8);
  tcase_add_test(tc1_1, test_calculation_error_9);

  tcase_add_test(tc1_1, test_calculation_error_10);
  tcase_add_test(tc1_1, test_calculation_error_11);
  tcase_add_test(tc1_1, test_calculation_error_12);
  tcase_add_test(tc1_1, test_calculation_error_13);
  tcase_add_test(tc1_1, test_calculation_error_14);
  tcase_add_test(tc1_1, test_calculation_error_15);
  tcase_add_test(tc1_1, test_calculation_error_16);
  tcase_add_test(tc1_1, test_calculation_error_17);
  tcase_add_test(tc1_1, test_calculation_error_18);

  suite_add_tcase(s, tc1_1);
  return s;
}

Suite *tests_hard_case(void) {
  Suite *s = suite_create("hard_case");
  TCase *tc1_1 = tcase_create("calc");

  tcase_add_test(tc1_1, test_hard_case_1);
  tcase_add_test(tc1_1, test_hard_case_2);
  tcase_add_test(tc1_1, test_hard_case_3);
  tcase_add_test(tc1_1, test_hard_case_4);
  tcase_add_test(tc1_1, test_hard_case_5);
  tcase_add_test(tc1_1, test_hard_case_6);
  tcase_add_test(tc1_1, test_hard_case_7);
  tcase_add_test(tc1_1, test_hard_case_8);
  tcase_add_test(tc1_1, test_hard_case_9);
  tcase_add_test(tc1_1, test_hard_case_10);
  tcase_add_test(tc1_1, test_hard_case_11);

  suite_add_tcase(s, tc1_1);
  return s;
}

Suite *tests_x_case_error(void) {
  Suite *s = suite_create("x_case_error");
  TCase *tc1_1 = tcase_create("calc");

  tcase_add_test(tc1_1, test_x_case_error_1);
  tcase_add_test(tc1_1, test_x_case_error_2);
  tcase_add_test(tc1_1, test_x_case_error_3);
  tcase_add_test(tc1_1, test_x_case_error_4);
  tcase_add_test(tc1_1, test_x_case_error_5);
  tcase_add_test(tc1_1, test_x_case_error_6);
  tcase_add_test(tc1_1, test_x_case_error_7);
  tcase_add_test(tc1_1, test_x_case_error_8);

  suite_add_tcase(s, tc1_1);
  return s;
}

Suite *tests_x_case(void) {
  Suite *s = suite_create("x_case");
  TCase *tc1_1 = tcase_create("calc");

  tcase_add_test(tc1_1, test_x_case_1);
  tcase_add_test(tc1_1, test_x_case_2);
  tcase_add_test(tc1_1, test_x_case_3);
  tcase_add_test(tc1_1, test_x_case_4);
  tcase_add_test(tc1_1, test_x_case_5);
  tcase_add_test(tc1_1, test_x_case_6);
  tcase_add_test(tc1_1, test_x_case_7);

  suite_add_tcase(s, tc1_1);
  return s;
}

int main(void) {
  int failed = 0;
  Suite *calc_tests[] = {tests_empty_and_invalid(),
                         tests_simple(),
                         tests_calculation_error(),
                         tests_hard_case(),
                         tests_x_case_error(),
                         tests_x_case(),
                         NULL};

  for (int i = 0; calc_tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(calc_tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  if (failed == 0) {
    printf("SUCCESS\n");
  } else {
    printf("FAILED\n");
  }

  return failed == 0 ? 0 : 1;
}
