/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unset_env.c
*/

#include <malloc.h>

#include "mysh.h"
#include "ice/string.h"

char **unset_env(env_t *env, char *name)
{
    ull_t i = 0;
    ull_t len = ice_strlen(name);

    for (; env->env[i] && ice_strncmp(env->env[i], name, len); i++);
    free(env->env[i]);
    for (; env->env[i]; i++)
        env->env[i] = env->env[i + 1];
    return env->env;
}
