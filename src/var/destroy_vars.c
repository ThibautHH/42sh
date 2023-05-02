/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** destroy_env.c
*/

#include <malloc.h>

#include "mysh.h"
#include "ice/array.h"

void destroy_vars(mysh_t *context, var_type_t type)
{
    var_t *var, *tmp;

    TAILQ_FOREACH_SAFE(var, VARQ, entries, tmp) {
        TAILQ_REMOVE(VARQ, var, entries);
        free(var);
    }
}
