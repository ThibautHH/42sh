/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** unset_env.c
*/

#include <malloc.h>
#include "ice/string.h"

char **unset_env(char **env, char *name)
{
    ull_t i = 0;
    ull_t len = ice_strlen(name);

    for (; env[i] && ice_strncmp(env[i], name, len); i++);
    free(env[i]);
    for (; env[i]; i++)
        env[i] = env[i + 1];
    return env;
}
