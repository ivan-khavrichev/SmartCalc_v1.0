#include "s21_calc.h"

int smart_calculation(char *str, double *result, double x, int check_x) {
  setlocale(LC_ALL, "en-US");
  setlocale(LC_NUMERIC, "C");

  stack *list = NULL;
  stack *list_polish = NULL;
  int status = OK;
  int step = 0;

  foolproofing(&str, &status);

  while (*str != '\0' && status == OK) {
    status = INVALID_VALUE;

    skip_space(&str, &status);
    parser_bracket(&list, &str, &status, &step);
    parser_function(&list, &str, &status, &step);
    parser_operators(&list, &str, &status, &step);
    parser_number(&list, &str, &status, &step);
    parser_variable(&list, &str, &status, &step, check_x);

    str += step;
    step = 0;
  }

  convert_polish(&list, &list_polish, &status);
  calculation(&list_polish, result, x, &status);

  free_list(&list);
  free_list(&list_polish);

  return status;
}

int calculation(stack **list_polish, double *answer, double x, int *status) {
  if (*status != OK) {
    return *status;
  }
  int flag_end = 0;
  stack *tmp = *list_polish;
  stack *list_answer = NULL;
  while (flag_end == 0 && *status == OK) {
    if (tmp->next == NULL) {
      flag_end = 1;
    }
    if (tmp->data.type == number) {
      push_stack(&list_answer, tmp->data);
    } else if (tmp->data.type == variable) {
      push_list(&list_answer, number, var_num, x, 'n', NULL);
    } else if (tmp->data.type == function || tmp->data.type == operat) {
      if (list_answer == NULL) {
        *status = CALCULATION_ERROR;
      } else {
        *status = tmp->data.func(&list_answer, &tmp);
      }
    }
    tmp = tmp->next;
  }
  if (list_answer != NULL) {
    if (list_answer->next != NULL) {
      *status = CALCULATION_ERROR;
    } else {
      *answer = list_answer->data.value;
    }
    free_list(&list_answer);
  }
  return *status;
}
