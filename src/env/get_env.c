/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** get_env.c
*/

#include "mysh.h"
#include "ice/string.h"

char *get_env(char *name, env_t *env)
{
    for (int i = 0; env->env[i]; i++)
        if (!ice_strncmp(env->env[i], name, ice_strlen(name)))
            return env->env[i] + ice_strlen(name) + 1;
    return NULL;
}
