/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** display_error.c
*/

#include "mysh.h"
#include "ice/printf.h"

void display_error(mysh_t *context, const char *format, const char *str)
{
    ice_printf(format, str);
    STATUS = 1;
    EXIT = true;
}
