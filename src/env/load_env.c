/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** load_env.c
*/

#include "mysh.h"
#include "ice/memory.h"

void load_env(mysh_t *context, char **env)
{
    for (; *env; env++)
        var_add(context, *env, VAR_ENV);
}
