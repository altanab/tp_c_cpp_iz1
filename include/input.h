#ifndef IZ_1_INPUT_H
#define IZ_1_INPUT_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char input_char();
char *input_string();
bool is_space(char);
char *get_trimmed_string(char const * const);
int input_int();
#endif //IZ_1_INPUT_H
