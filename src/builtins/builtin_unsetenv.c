/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_unsetenv.c
*/

#include "mysh/env.h"
#include "mysh/miscellaneous.h"

env_t *builtin_unsetenv(char **av, mysh_t *context)
{
    if (!av[1]) {
        display_error(context, "unsetenv: Too few arguments.\n", NULL);
        return ENV;
    }
    for (ull_t i = 1; av[i]; i++)
        ENV->env = unset_env(context, av[i]);
    return ENV;
}
