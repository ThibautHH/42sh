/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** dup_env.c
*/

#include <malloc.h>

#include "mysh.h"
#include "ice/string.h"

char **dup_env(char **env)
{
    ull_t size = 0;
    char **new_env;

    for (; env[size]; size++);
    new_env = malloc(sizeof(char *) * (size + 1));
    if (!new_env)
        return NULL;
    for (unsigned int i = 0 ; env[i] ; i++) {
        new_env[i] = ice_strdup(env[i]);
        if (!new_env[i])
            return NULL;
    }
    new_env[size] = NULL;
    return new_env;
}
