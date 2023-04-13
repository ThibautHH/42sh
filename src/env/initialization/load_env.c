/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** load_env.c
*/

#include "mysh/env.h"
#include "ice/memory.h"

env_t *load_env(char **env)
{
    env_t *new_env = ice_calloc(1, sizeof(env_t));

    if (!new_env)
        return NULL;
    new_env->env = dup_env(env);
    if (!new_env->env)
        return NULL;
    new_env->env = fix_env(new_env->env);
    return new_env->env ? new_env : NULL;
}