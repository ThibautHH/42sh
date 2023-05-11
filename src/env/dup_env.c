/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** dup_env.c
*/

#include <malloc.h>

#include "mysh.h"

char **dup_env(mysh_t *context)
{
    const var_type_t type = VAR_ENV;
    char **env = malloc(sizeof(char *) * (VARC + 1));
    var_t *env_var;
    size_t i = 0;

    if (!env)
        DIE;
    env[VARC] = NULL;
    TAILQ_FOREACH(env_var, VARQ, entries)
        env[i++] = VARN(env_var);
    return env;
}
