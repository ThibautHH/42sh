/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_env.c
*/

#include "mysh/env.h"
#include "ice/string.h"

char *get_env(mysh_t *context, char *name)
{
    for (int i = 0; ENV->env[i]; i++)
        if (!ice_strncmp(ENV->env[i], name, ice_strlen(name)))
            return ENV->env[i] + ice_strlen(name) + 1;
    return NULL;
}
