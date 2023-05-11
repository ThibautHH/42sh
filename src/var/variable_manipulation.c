/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** environment_manipulation.c
*/

#include <malloc.h>

#include "mysh.h"

bool is_var_named(var_t *var, char *name)
{
    size_t nlen = ice_strlen(name);

    return (nlen == ice_strtil(VARN(var), '='))
        && (!ice_strncmp2(VARN(var), name, nlen));
}

var_t *var_get(mysh_t *context, char *name, var_type_t type)
{
    var_t *var;

    TAILQ_FOREACH(var, VARQ, entries)
        if (is_var_named(var, name))
            return var;
    return NULL;
}

void var_add(mysh_t *context, char *var_str, var_type_t type)
{
    var_t *var = malloc(sizeof(var_t));

    if (!var)
        DIE;
    var->name = &(*VARV(var)) - (ice_strtil(var_str, '=') + 1);
    ice_strcpy(VARN(var), var_str);
    TAILQ_INSERT_TAIL(VARQ, var, entries);
    VARC++;
}

void var_update(mysh_t *context, char *name, char *value, var_type_t type)
{
    var_t *var;

    TAILQ_FOREACH(var, VARQ, entries)
        if (is_var_named(var, name)) {
            ice_strcpy(VARV(var), value);
            return;
        }
    var = malloc(sizeof(var_t));
    if (!var)
        DIE;
    var->name = &(*VARV(var)) - (ice_strlen(name) + 1);
    ice_strcpy(VARN(var), name);
    ice_strcpy(VARV(var), value);
    VARV(var)[-1] = '=';
    TAILQ_INSERT_TAIL(VARQ, var, entries);
    VARC++;
}

void var_remove(mysh_t *context, char *name, var_type_t type)
{
    var_t *var;
    var_t *tmp;

    TAILQ_FOREACH_SAFE(var, VARQ, entries, tmp)
        if (is_var_named(var, name)) {
            TAILQ_REMOVE(VARQ, var, entries);
            free(var);
            VARC--;
            return;
        }
}
