#include "s21_calc.h"

int unar_function(stack **list_numbers, stack **list_operators,
                  double (*func_unar)(double)) {
  int status = CALCULATION_ERROR;
  stack *tmp_numbers = *list_numbers;
  stack *tmp_operators = *list_operators;
  if (tmp_numbers != NULL && tmp_operators != NULL) {
    while (tmp_numbers->next != NULL) {
      tmp_numbers = (stack *)tmp_numbers->next;
    }
    double num = tmp_numbers->data.value;
    double new_num = func_unar(num);
    tmp_numbers->data.value = new_num;
    status = OK;
  }
  return status;
}

int binar_function(stack **list_numbers, stack **list_operators,
                   double (*func_binar)(double, double)) {
  int status = CALCULATION_ERROR;
  stack *number_2 = *list_numbers;
  stack *number_1 = NULL;
  if (number_2 != NULL && number_2->next != NULL && *list_operators != NULL) {
    while (number_2->next != NULL) {
      number_1 = number_2;
      number_2 = (stack *)number_2->next;
    }
    double num_1 = number_1->data.value;
    double num_2 = number_2->data.value;
    double new_num = func_binar(num_1, num_2);
    number_1->data.value = new_num;
    pop_stack(list_numbers);
    status = OK;
  }
  return status;
}

double my_plus(double number) { return number; }

double my_minus(double number) { return (-1 * number); }

double my_sum(double number_1, double number_2) {
  return (number_1 + number_2);
}

double my_sub(double number_1, double number_2) {
  return (number_1 - number_2);
}

double my_mul(double number_1, double number_2) {
  return (number_1 * number_2);
}

double my_div(double number_1, double number_2) {
  return (number_1 / number_2);
}

int math_cos(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &cos);
}

int math_sin(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &sin);
}

int math_tan(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &tan);
}

int math_acos(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &acos);
}

int math_asin(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &asin);
}

int math_atan(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &atan);
}

int math_sqrt(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &sqrt);
}

int math_ln(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &log);
}

int math_log(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &log10);
}

int math_plus(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &my_plus);
}

int math_minus(stack **list_numbers, stack **list_operators) {
  return unar_function(list_numbers, list_operators, &my_minus);
}

int math_sum(stack **list_numbers, stack **list_operators) {
  return binar_function(list_numbers, list_operators, &my_sum);
}

int math_sub(stack **list_numbers, stack **list_operators) {
  return binar_function(list_numbers, list_operators, &my_sub);
}

int math_mul(stack **list_numbers, stack **list_operators) {
  return binar_function(list_numbers, list_operators, &my_mul);
}

int math_div(stack **list_numbers, stack **list_operators) {
  return binar_function(list_numbers, list_operators, &my_div);
}

int math_pow(stack **list_numbers, stack **list_operators) {
  return binar_function(list_numbers, list_operators, &pow);
}

int math_mod(stack **list_numbers, stack **list_operators) {
  return binar_function(list_numbers, list_operators, &fmod);
}
