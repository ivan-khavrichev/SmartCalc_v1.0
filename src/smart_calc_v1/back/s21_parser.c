#include "s21_calc.h"

void foolproofing(char **str, int *status) {
  if (strlen(*str) == 0) {
    *status = EMPTY_INPUT;
  } else if (strlen(*str) != 0 && **str == ' ') {
    *status = EMPTY_INPUT;
    while (**str != '\0' && *status != OK) {
      *str += 1;
      if (**str != ' ' && **str != '\0') {
        *status = OK;
      }
    }
  }
}

void skip_space(char **str, int *status) {
  while (**str == ' ') {
    *str += 1;
  }
  if (**str == '\0') {
    *status = OK;
  }
}

void parser_bracket(stack **list, char **str, int *status, int *step) {
  if (**str == '(') {
    push_list(list, bracket_o, 0, 0, '(', NULL);
    *status = OK;
    *step += 1;
  } else if (**str == ')') {
    push_list(list, bracket_c, 0, 0, ')', NULL);
    *status = OK;
    *step += 1;
  }
}

void parser_function(stack **list, char **str, int *status, int *step) {
  char functions[9][5] = {"cos",  "sin",  "tan", "acos", "asin",
                          "atan", "sqrt", "ln",  "log"};
  char symbols[9] = {'c', 's', 't', 'C', 'S', 'T', 'q', 'l', 'L'};
  int (*math_function[9])(stack **, stack **) = {
      &math_cos,  &math_sin,  &math_tan, &math_acos, &math_asin,
      &math_atan, &math_sqrt, &math_ln,  &math_log};
  char *str_found = NULL;
  int len = 0;
  for (int i = 0; i < 9 && *str != str_found; i++) {
    str_found = strstr(*str, functions[i]);
    len = strlen(functions[i]);
    if (*str == str_found) {
      push_list(list, function, func, 0, symbols[i], math_function[i]);
      *status = OK;
      *step += len;
    }
  }
}

void parser_operators(stack **list, char **str, int *status, int *step) {
  char operators[6][4] = {"*", "/", "^", "mod", "+", "-"};
  int (*math_operators[8])(stack **, stack **) = {
      &math_mul, &math_div, &math_pow,  &math_mod,
      &math_sum, &math_sub, &math_plus, &math_minus};
  char *str_found = NULL;
  int len = 0;
  for (int i = 0; i < 6 && *str != str_found; i++) {
    str_found = strstr(*str, operators[i]);
    len = strlen(operators[i]);
    if (*str == str_found) {
      int precedence = prioritize(list, *str_found);
      int unar_factor = check_unar_binar(list, *str_found);
      push_list(list, operat, precedence, 0, *str_found,
                math_operators[i + unar_factor]);
      *status = OK;
      *step += len;
    }
  }
}

void parser_number(stack **list, char **str, int *status, int *step) {
  int flag_digit = 0;
  int flag_point = 0;
  int flag_exp = 0;
  int step_num = check_number(*str, &flag_digit, &flag_point, &flag_exp);
  if (step_num != 0) {
    char *str_start = *str;
    *str += step_num;
    while (step_num != 0 && **str != '\0') {
      step_num = check_number(*str, &flag_digit, &flag_point, &flag_exp);
      *str += step_num;
    }
    if (flag_point < 2 && flag_exp < 2) {
      char str_number[255] = {0};
      double num = 0;
      strncpy(str_number, str_start, *str - str_start);
      num = atof(str_number);
      *str = str_start;
      push_list(list, number, var_num, num, 'n', NULL);
      *status = OK;
      *step += strlen(str_number);
    }
  } else if (**str == 'p' && *(*str += 1) == 'i') {
    push_list(list, number, var_num, M_PI, 'p', NULL);
    *status = OK;
    *step += 1;
  } else if (**str == 'e') {
    push_list(list, number, var_num, M_E, 'e', NULL);
    *status = OK;
    *step += 1;
  }
}

int check_number(char *str, int *flag_digit, int *flag_point, int *flag_exp) {
  int len = 0;
  if (isdigit(*str) != 0) {
    *flag_digit += 1;
    len = 1;
  } else if (*str == '.') {
    *flag_point += 1;
    len = 1;
  } else if (*str == 'E' && (*(str + 1) == '+' || *(str + 1) == '-')) {
    *flag_exp += 1;
    len = 2;
  } else if (*str == 'E') {
    *flag_exp += 1;
    len = 1;
  }
  if (*flag_exp == 1 && *flag_digit == 0 && *flag_point == 0) {
    len = 0;
  }
  return len;
}

void parser_variable(stack **list, char **str, int *status, int *step,
                     int check_x) {
  if (**str == 'x') {
    push_list(list, variable, var_num, 0, 'x', NULL);
    if (check_x == 0) {
      *status = OK;
      *step += 1;
    } else {
      *status = INVALID_X;
    }
  }
}

int check_unar_binar(stack **list, char symbol) {
  int status = 0;
  if (symbol == '-' || symbol == '+') {
    if (*list == NULL) {
      status = UNAR;
    } else {
      stack *p = *list;
      while (p->next != NULL) {
        p = (stack *)p->next;
      }
      if (p->data.type == operat || p->data.type == bracket_o) {
        status = UNAR;
      }
    }
  }
  return status;
}

int prioritize(stack **list, char symbol) {
  int precedence = 0;
  if (symbol == '^') {
    precedence = func;
  } else if (symbol != '-' && symbol != '+') {
    precedence = oper;
  } else if ((symbol == '-' || symbol == '+') &&
             check_unar_binar(list, symbol) == UNAR) {
    precedence = un_oper;
  } else {
    precedence = bin_oper;
  }
  return precedence;
}
