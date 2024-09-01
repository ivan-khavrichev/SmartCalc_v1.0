/*!
\file
\brief Заголовочный файл с описанием функций, применяемых для осуществления
вычислений

Данный файл содержит в себе определения
функций, используемых в проекте SmartCalc v1.0.
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0  ///< код успешного завершения работы функции
#define EMPTY_INPUT 1  ///< код ошибки, возникаемой при введении пустой строки
#define INVALID_VALUE \
  2  ///< код ошибки, возникаемой при введении некорректной строки
#define CALCULATION_ERROR \
  3  ///< код ошибки, возникаемой при введении некорректного маетматического
     ///< выражения
#define INVALID_X \
  4  ///< код ошибки, возникаемой при введении некорректной переменной

#define EMPTY -1  ///< код успешного завершения работы функции, принимающей
#define UNAR 2  ///< код возвращения унарного оператора

#define MAX_VALUE \
  1000000.0  ///< ограничивает область определения и область значения функций
             ///< сверху
#define MIN_VALUE \
  -1000000.0  ///< ограничивает область определения и область значения функций
              ///< снизу

typedef struct stack stack;

/**
 * @brief Тип данных - указатель на функцию. Функция, находящая в структуре
 * лексемы
 */
typedef int (*math_function)(stack **, stack **);

/**
 * @brief Тип данных - указатель на функцию. Функция унарная: принимает одно
 * число
 */
typedef double (*func_unar)(double);

/**
 * @brief Тип данных - указатель на функцию. Функция бинарная: принимает два
 * числа
 */
typedef double (*func_binar)(double, double);

/**
 * @brief  Перечисление, используемое в стеке лексем для обозначения приоритета
 */
typedef enum {
  var_num,   ///< приоритет числа и переменной
  bin_oper,  ///< приоритет бинарных операций: + и -
  oper,
  func,  ///< приоритет других операций и функций
  un_oper  ///< приоритет унарных операций: + и -
} priority_lexeme;

/**
 * @brief Перечисление, используемое в стеке лексем для обозначения типа лексемы
 */
typedef enum {
  variable,   ///< перменная
  number,     ///< число
  operat,     ///< оператор
  function,   ///< функция
  bracket_o,  ///< открывающая скобка
  bracket_c   ///< закрывающая скобка
} type_lexeme;

/**
 * @brief Структура, с характеристиками лексем стека
 */
typedef struct {
  int type;            ///< тип лексемы
  int priority;        ///< приоритет лексемы
  double value;        ///< значение числа
  char symbol;         ///< символ
  math_function func;  ///< указатель на функцию, callback
} lexeme;

/**
 * @brief Стек с лексемами введённой строки
 */
struct stack {
  lexeme data;  ///< структура лексемы с её характеристиками
  struct stack *next;  ///< указатель на следующий элемент стека
};

/**
 * @brief функция защиты от дурака, валидирует строку на пустоту
 *  изменяет статус на 1, если строка пустая, если в ней только пробелы
 * @param str введённая строка
 * @param status статус ошибки
 */
void foolproofing(char **str, int *status);

/**
 * @brief функция пропуска пробела в строке
 * @param str введённая строка
 * @param status статус ошибки
 */
void skip_space(char **str, int *status);

/**
 * @brief функция парсера строки, определяет лексемы, как функции
 * изменяют статус на OK, если лексема найдена успешно
 * @param list стек с лексемами введённой строки
 * @param str введённая строка
 * @param status статус ошибки
 * @param step шаг сдвига по строке
 */
void parser_function(stack **list, char **str, int *status, int *step);

/**
 * @brief функция парсера строки, определяет лексемы, как скобки
 * изменяют статус на OK, если лексема найдена успешно
 * @param list стек с лексемами введённой строки
 * @param str введённая строка
 * @param status статус ошибки
 * @param step шаг сдвига по строке
 */
void parser_bracket(stack **list, char **str, int *status, int *step);

/**
 * @brief функция парсера строки, определяет лексемы, как операторы
 * изменяют статус на OK, если лексема найдена успешно
 * @param list стек с лексемами введённой строки
 * @param str введённая строка
 * @param status статус ошибки
 * @param step шаг сдвига по строке
 */
void parser_operators(stack **list, char **str, int *status, int *step);

/**
 * @brief функция парсера строки, определяет лексемы, как числа
 * изменяют статус на OK, если лексема найдена успешно
 * @param list стек с лексемами введённой строки
 * @param str введённая строка
 * @param status статус ошибки
 * @param step шаг сдвига по строке
 */
void parser_number(stack **list, char **str, int *status, int *step);

/**
 * @brief функция парсера строки, определяет лексемы, как переменной
 * изменяют статус на OK, если лексема найдена успешно
 * @param list стек с лексемами введённой строки
 * @param str введённая строка
 * @param status статус ошибки
 * @param step шаг сдвига по строке
 * @param check_x статус наличия переменной в строке
 */
void parser_variable(stack **list, char **str, int *status, int *step,
                     int check_x);

/**
 * @brief функция проверки корректной записи числа;
 * через указатели на флаги подсчитывает количество точек и степеней в числе
 * @param str  введённая строка
 * @param flag_digit  счётчик чисел
 * @param flag_point  счётчик точек
 * @param flag_exp  счётчик экспоненты
 * @return int величина сдвига строки: если число начинается со степени; 0, если
 * число некорректное
 */
int check_number(char *str, int *flag_digit, int *flag_point, int *flag_exp);

/**
 * @brief функция для определения бинарности-унарности "+" и "-"
 * @param list стек с лексемами введённой строки
 * @param symbol символ строки
 * @return int 2, если унарный и 0, если бинарный
 */
int check_unar_binar(stack **list, char symbol);

/**
 * @brief функция выставления приоритета для операторов
 * @param list стек с лексемами введённой строки
 * @param symbol символ строки
 * @return int  1, если бинарный "+" или "-";
 * 4, если унарный "+" или "-", 2, если другие операторы
 */
int prioritize(stack **list, char symbol);

/**
 * @brief функция вносит структуру в список
 * @param list стек, в который нужно занести лексему
 * @param value лексема, которая вносится в стек
 */
void push_stack(stack **list, lexeme value);

/**
 * @brief функция удаляет последнюю структуру из списка
 * @param list стек, из которого нужно удалить лексему
 */
void pop_stack(stack **list);

/**
 * @brief функция возврата последней лексемы из списка
 * @param list_tmp список лексем
 * @return lexeme последнюю лексему, если лексемы в списке нет
 * лексем, лексему с параметрами, равными -1
 */
lexeme last_lexeme(stack **list_tmp);

/**
 * @brief функция для заполнения характеристик лексемам и её запись в стек
 * @param list стек, который заполняется
 * @param type тип лексемы
 * @param priority приоритет лексемы
 * @param value значение числа
 * @param symbol символ
 * @param math_function указатель на функцию, callback
 */
void push_list(stack **list, int type, int priority, double value, char symbol,
               int (*math_function)(stack **, stack **));

/**
 * @brief функция обработки унарных операций и функций
 * @param list_numbers стек с числами
 * @param list_operators стек с опретаорами
 * @param func_unar ссылка на унарные функции
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int unar_function(stack **list_numbers, stack **list_operators,
                  double (*func_unar)(double));

/**
 * @brief  функция обработки бинарных операций и функций
 * @param list_numbers стек с числами
 * @param list_operators стек с опретаорами
 * @param func_binar ссылка на бинарные функции
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int binar_function(stack **list_numbers, stack **list_operators,
                   double (*func_binar)(double, double));

/**
 * @brief функция косинуса, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_cos(stack **list_numbers, stack **list_operators);

/**
 * @brief функция синуса, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_sin(stack **list_numbers, stack **list_operators);

/**
 * @brief функция тангенса, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_tan(stack **list_numbers, stack **list_operators);

/**
 * @brief функция аргкосинуса, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_acos(stack **list_numbers, stack **list_operators);

/**
 * @brief функция аргсинуса, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_asin(stack **list_numbers, stack **list_operators);

/**
 * @brief функция аргтангенса, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_atan(stack **list_numbers, stack **list_operators);

/**
 * @brief функция квадратного корня, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_sqrt(stack **list_numbers, stack **list_operators);

/**
 * @brief функция натурального логарифма, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_ln(stack **list_numbers, stack **list_operators);

/**
 * @brief функция десятичного логарифма, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_log(stack **list_numbers, stack **list_operators);

/**
 * @brief функция плюса, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int  1, если операцию провести невозможно, иначе 0
 */
int math_plus(stack **list_numbers, stack **list_operators);

/**
 * @brief функция минуса, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_minus(stack **list_numbers, stack **list_operators);

/**
 * @brief функция сложения, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_sum(stack **list_numbers, stack **list_operators);

/**
 * @brief функция вычитания, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_sub(stack **list_numbers, stack **list_operators);

/**
 * @brief функция умножения, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_mul(stack **list_numbers, stack **list_operators);

/**
 * @brief функция деления, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_div(stack **list_numbers, stack **list_operators);

/**
 * @brief функция возведения в степень, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_pow(stack **list_numbers, stack **list_operators);

/**
 * @brief функция деления с остатком, передаваемая в структуру лексемы
 * @param list_numbers стек чисел
 * @param list_operators стек операторов
 * @return int 1, если операцию провести невозможно, иначе 0
 */
int math_mod(stack **list_numbers, stack **list_operators);

// функции унарные и бинарные
// унарные принимают одно число, бинарные - два
// все функции возвращают результат выполнения операций

/**
 * @brief унарная функция плюса, вычисляет знак числа
 * @param number число
 * @return double вычисленное значение
 */
double my_plus(double number);

/**
 * @brief унарная функция минуса, вычисляет знак числа
 * @param number число
 * @return double вычисленное значение
 */
double my_minus(double number);

/**
 * @brief бинарная функция суммы, вычисляет сумму двух чисел
 * @param number число
 * @return double вычисленное значение
 */
double my_sum(double number_1, double number_2);

/**
 * @brief бинарная функция вычитания, вычисляет разность двух чисел
 * @param number число
 * @return double вычисленное значение
 */
double my_sub(double number_1, double number_2);

/**
 * @brief бинарная функция умножения, вычисляет произведение двух чисел
 * @param number число
 * @return double вычисленное значение
 */
double my_mul(double number_1, double number_2);

/**
 * @brief бинарная функция деления, вычисляет частное двух чисел
 * @param number число
 * @return double вычисленное значение
 */
double my_div(double number_1, double number_2);

/**
 * @brief функция конвертации записи в инфиксной форме в постфиксную
 * с помощью алгоритма «сортировочная станция»
 * @param list стек лексем
 * @param list_polish стек, куда будут записаны лексемы в постфиксной форме
 * @param status статус ошибки, если ошибка, если успешно 0
 * @return int статус ошибки, если ошибка, если успешно 0
 */
int convert_polish(stack **list, stack **list_polish, int *status);

/**
 * @brief функция очистки временного стека
 * добавляет верхний элемент стека в выходную запись и удаляет этот элемент
 * @param list_polish стек, куда будут записаны лексемы в постфиксной форме
 * @param list_tmp временный стек, для реализации алгоритма «сортировочная
 * станция»
 * @param operat последняя лексема во временном стеке
 * @return int 1, если в стеке лишняя скобка, иначе 0
 */
int empty_stack_polish(stack **list_polish, stack **list_tmp, lexeme *operat);

/**
 * @brief функция вычисления введённой строки
 * @param list_polish стек с лексемами, записанными в постфиксной форме
 * @param answer переменная для записи итога вычислений
 * @param x значение переменной
 * @param status статус наличия значения переменной
 * @return int стутус ошибки, если она была, иначе 0
 */
int calculation(stack **list_polish, double *answer, double x, int *status);

/**
 * @brief функция очистки стека
 * удаляет все элементы стека, присваивает NULL указателю на него
 * @param list стек, который нужно удалить
 */
void free_list(stack **list);

/**
 * @brief итоговая функци калькулятора
 * @param str введённая строка
 * @param result переменная для записи итога вычислений
 * @param x значение переменной
 * @param check_x статус наличия значения переменной
 * @return int статус ошибки, если допущена ошибка, иначе 0
 */
int smart_calculation(char *str, double *result, double x, int check_x);

#ifdef __cplusplus
}
#endif
