/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_env.c
*/

#include <stdio.h>

#include "mysh.h"

void builtin_at(mysh_t *context)
{
    var_t *var;
    var_type_t type = VAR_SHELL;

    TAILQ_FOREACH(var, VARQ, entries) {
        VARV(var)[-1] = '\t';
        PRINT("%s\n", var->name);
        VARV(var)[-1] = '=';
    }
    STATUS = 0;
}
