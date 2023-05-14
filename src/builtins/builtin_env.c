/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_env.c
*/

#include <stdio.h>

#include "mysh.h"

void builtin_env(mysh_t *context)
{
    var_t *var;
    var_type_t type = VAR_ENV;

    TAILQ_FOREACH(var, VARQ, entries)
        PRINT("%s\n", var->name);
    STATUS = 0;
}
