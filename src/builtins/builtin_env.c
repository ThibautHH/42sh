/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_env.c
*/

#include "mysh.h"

bool builtin_env(mysh_t *context)
{
    display_env(context);
    return (STATUS = 0);
}
