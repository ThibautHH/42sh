/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unset_env.c
*/

#include <malloc.h>

#include "mysh/env.h"
#include "ice/string.h"

char **unset_env(mysh_t *context, char *name)
{
    ull_t i = 0;
    ull_t len = ice_strlen(name);

    for (; ENV->env[i] && ice_strncmp(ENV->env[i], name, len); i++);
    free(ENV->env[i]);
    for (; ENV->env[i]; i++)
        ENV->env[i] = ENV->env[i + 1];
    return ENV->env;
}
