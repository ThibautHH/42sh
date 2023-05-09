/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_env.c
*/

#include "ice/printf.h"

#include "mysh.h"

void builtin_env(mysh_t *context)
{
    var_t *var; var_type_t type = VAR_ENV;
    TAILQ_FOREACH(var, VARQ, entries)
        if (ice_printf("%s\n", var->name) < 0)
            DIE;
    STATUS = 0;
}
