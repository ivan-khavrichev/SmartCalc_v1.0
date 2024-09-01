#include "s21_calc.h"

void push_stack(stack **list, lexeme value) {
  stack *tmp = (stack *)calloc(sizeof(stack), sizeof(stack));
  if (*list != NULL) {
    tmp->data = value;
    tmp->next = NULL;
    stack *p = *list;
    while (p->next != NULL) {
      p = (stack *)p->next;
    }
    p->next = (struct stack *)tmp;
  } else {
    tmp->data = value;
    tmp->next = NULL;
    *list = tmp;
  }
}

void pop_stack(stack **list) {
  stack *tmp = *list;
  if (tmp != NULL && tmp->next != NULL) {
    stack *cur = tmp;
    stack *prev = NULL;
    while (cur->next != NULL) {
      prev = cur;
      cur = (stack *)cur->next;
    }
    prev->next = NULL;
    free(cur);
  } else if (tmp->next == NULL) {
    tmp->next = NULL;
    free(*list);
    *list = NULL;
  }
}

void push_list(stack **list, int type, int priority, double value, char symbol,
               int (*math_function)(stack **, stack **)) {
  lexeme lex = {0};
  lex.type = type;
  lex.priority = priority;
  lex.value = value;
  lex.symbol = symbol;
  lex.func = math_function;
  push_stack(list, lex);
}

lexeme last_lexeme(stack **list_tmp) {
  stack *p = *list_tmp;
  lexeme last_lexeme = {-1, -1, -1, '1', NULL};
  if (p != NULL) {
    while (p->next != NULL) {
      p = (stack *)p->next;
    }
    last_lexeme = p->data;
  }
  return last_lexeme;
}

void free_list(stack **list) {
  while (*list != NULL) {
    pop_stack(list);
  }
}
