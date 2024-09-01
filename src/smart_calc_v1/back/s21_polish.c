#include "s21_calc.h"

int convert_polish(stack **list, stack **list_polish, int *status) {
  if (*status != OK) {
    return *status;
  }
  int flag_end = 0;
  stack *tmp = *list;
  stack *list_tmp = NULL;
  while (flag_end == 0) {
    if (tmp->next == NULL) {
      flag_end = 1;
    }
    if (tmp->data.type == number || tmp->data.type == variable) {
      push_stack(list_polish, tmp->data);
    } else if (tmp->data.type == function || tmp->data.type == bracket_o) {
      push_stack(&list_tmp, tmp->data);
    } else if (tmp->data.type == operat) {
      lexeme operator= last_lexeme(&list_tmp);
      while (operator.priority >= tmp->data.priority) {
        empty_stack_polish(list_polish, &list_tmp, &operator);
      }
      push_stack(&list_tmp, tmp->data);
    } else if (tmp->data.type == bracket_c) {
      lexeme operator= last_lexeme(&list_tmp);
      while (operator.type != bracket_o && operator.type != EMPTY) {
        empty_stack_polish(list_polish, &list_tmp, &operator);
      }
      if (operator.type == bracket_o) {
        pop_stack(&list_tmp);
        operator= last_lexeme(&list_tmp);
        if (operator.type == function) {
          empty_stack_polish(list_polish, &list_tmp, &operator);
        }
        if (operator.priority == un_oper) {
          empty_stack_polish(list_polish, &list_tmp, &operator);
        }
      } else {
        *status = CALCULATION_ERROR;
      }
    }
    tmp = tmp->next;
  }
  lexeme operator= last_lexeme(&list_tmp);
  if (operator.type == bracket_o || operator.type == bracket_c) {
    *status = CALCULATION_ERROR;
  } else {
    while (list_tmp != NULL && *status != CALCULATION_ERROR) {
      *status = empty_stack_polish(list_polish, &list_tmp, &operator);
    }
  }
  if (list_tmp != NULL) {
    free_list(&list_tmp);
  }
  if (*list_polish == NULL) {
    *status = CALCULATION_ERROR;
  }
  return *status;
}

int empty_stack_polish(stack **list_polish, stack **list_tmp, lexeme *operat) {
  int status = OK;
  push_stack(list_polish, *operat);
  pop_stack(list_tmp);
  *operat = last_lexeme(list_tmp);
  if ((operat->type == bracket_c || operat->type == bracket_o)) {
    status = CALCULATION_ERROR;
  }
  return status;
}
