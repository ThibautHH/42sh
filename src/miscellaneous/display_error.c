/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** display_error.c
*/

#include "mysh.h"
#include "ice/printf.h"

void display_error(env_t *env, const char *format, const char *str)
{
    ice_printf(format, str);
    env->status = 1;
    env->exit = true;
}
