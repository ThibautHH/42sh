/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_env.c
*/

#include "mysh/env.h"

env_t *builtin_env(UNUSED char **av, mysh_t *context)
{
    display_env(context);
    return ENV;
}
