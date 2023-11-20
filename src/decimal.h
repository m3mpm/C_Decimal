#ifndef SRC_DECIMAL_H_
#define SRC_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>

#define EXP_MASK 0x00ff0000;
#define NULL_SCALE 0x80000000;
#define NULL_MASK 0x00000000;
#define DECIMAL_NORMAL {{0, 0, 0, 0}, my_NORMAL_VALUE};
#define DECIMAL_NORMAL_SUPER {{0, 0, 0, 0, 0, 0, 0}, my_NORMAL_VALUE};

enum { LOW, MID, HIGH, SCALE };
enum { NLOW, NMID, NHIGH, SLOW, SMID, SHIGH, SSCALE };

typedef enum {
  my_NORMAL_VALUE = 0,
  my_INFINITY = 1,
  my_NEGATIVE_INFINITY = 2,
  my_NAN = 3
} value_type_t;

typedef struct {
  unsigned int bits[4];
  value_type_t value_type;
} my_decimal;

typedef struct {
  unsigned int bits[7];
  value_type_t value_type;
} my_decimal_super;

//  Арифметические операторы
//  При ошибке во время операции в переменную value_type записывается тип ошибки
my_decimal my_add(my_decimal, my_decimal);
my_decimal my_sub(my_decimal, my_decimal);
my_decimal my_mul(my_decimal, my_decimal);
my_decimal my_div(my_decimal, my_decimal);
my_decimal my_mod(my_decimal, my_decimal);

//  Операторы сравнение
//  Возвращаемое значение: 0 - TRUE, 1 - FALSE
int my_is_less(my_decimal, my_decimal);
int my_is_less_or_equal(my_decimal, my_decimal);
int my_is_greater(my_decimal, my_decimal);
int my_is_greater_or_equal(my_decimal, my_decimal);
int my_is_equal(my_decimal, my_decimal);
int my_is_not_equal(my_decimal, my_decimal);

//  Преобразователи
//  Возвращаемое значение - код ошибки: 0 - SUCCESS, 1 - CONVERTING ERROR
int my_from_int_to_decimal(int src, my_decimal *dst);
int my_from_float_to_decimal(float src, my_decimal *dst);
int my_from_decimal_to_int(my_decimal src, int *dst);
int my_from_decimal_to_float(my_decimal src, float *dst);

//  Другие функции
my_decimal my_floor(my_decimal);
my_decimal my_round(my_decimal);
my_decimal my_truncate(my_decimal);
my_decimal my_negate(my_decimal);

//  Вспомогательные функции
void my_decimal_set_default(my_decimal *dst);

// Установка и получение bit, scale
int my_getBit(my_decimal src, int i);
void my_setBit(my_decimal *dst, int i, int value);
int my_getScale(my_decimal src);
void my_setScale(my_decimal *dst, int value);
int my_getFloatExp(float src);
int my_getBitFloat(float src, int i);

// Функции установки знака "-" или "+" в SCALE*/
void my_setSign(my_decimal *dst, int value);
int my_getSign(my_decimal src);  // функция получения знака числа

// Умножение decimal на 10 */
my_decimal my_multi_10(my_decimal src);
// Сдвиг влево
my_decimal my_move_left(my_decimal src, int shift);
// Функция установки в decimal inf + super decimal inf
my_decimal my_decimal_set_inf(int sign);

// Функции выравнивания scale
void my_equality_scale(my_decimal *dec1, my_decimal *dec2);
my_decimal my_increase_scale(int diffScale, my_decimal src);

// Функция деления decimal на 10
my_decimal my_div_10_decimal(my_decimal);
int my_decimal_equal_int(my_decimal dec, unsigned int value);
int my_move_left_for_div(my_decimal dec1, my_decimal *dec2);
my_decimal my_move_right(my_decimal src, int shift);
int my_mod_div_10(my_decimal src_s);

/*------- super decimal fuctions start -----------*/
my_decimal_super my_convert_to_super(my_decimal);
void my_displayBits_super(my_decimal_super);
void my_equality_scale_super(my_decimal_super *dec1_s,
                              my_decimal_super *dec2_s);
my_decimal_super my_increase_scale_super(int diffScale,
                                           my_decimal_super src_s);
my_decimal_super my_multi_10_super(my_decimal_super src_s);
my_decimal_super my_move_left_super(my_decimal_super src_s, int shift);
my_decimal_super my_super_set_inf(int sign);
my_decimal_super my_add_simple_super(my_decimal_super dec1_s,
                                       my_decimal_super dec2_s);

int my_getBit_super(my_decimal_super src_s, int i);
int my_getSign_super(my_decimal_super src_s);
void my_setBit_super(my_decimal_super *dst_s, int i, int value);
void my_setScale_super(my_decimal_super *dst_s, int value);
int my_getScale_super(my_decimal_super src);
void my_setSign_super(my_decimal_super *dst, int value);
my_decimal my_convert_to_decimal(my_decimal_super);
my_decimal_super my_div_10_super(my_decimal_super src_s);
my_decimal_super my_sub_simple_super(my_decimal_super dec1_s, my_decimal_super dec2_s);
int my_mod_div_10_super(my_decimal_super src_s);
my_decimal_super my_move_right_super(my_decimal_super src, int shift);
int my_move_left_for_div_super(my_decimal_super dec1, my_decimal_super *dec2);
my_decimal_super my_mod_super(my_decimal_super dec1, my_decimal_super dec2);
my_decimal_super my_div_simple_super(my_decimal_super dec1, my_decimal_super dec2);
int my_is_greater_or_equal_super(my_decimal_super dec1_s, my_decimal_super dec2_s);
int my_is_greater_super(my_decimal_super dec1_s, my_decimal_super dec2_s);
int my_is_equal_super(my_decimal_super dec1_s, my_decimal_super dec2_s);
int my_decimal_is_equal_null_super(my_decimal_super dec);
/*------- super decimal fuctions end -----------*/

#endif  //  SRC_DECIMAL_H_
