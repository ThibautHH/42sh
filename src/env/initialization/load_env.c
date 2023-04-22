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
        env_add(context, *env);
}
