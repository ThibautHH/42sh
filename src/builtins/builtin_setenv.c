/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_setenv.c
*/

#include "mysh/env.h"
#include "ice/array.h"
#include "mysh/miscellaneous.h"

env_t *builtin_setenv(char **av, mysh_t *context)
{
    ull_t av_len = ice_array_len((void **)av);

    switch (av_len) {
        case 1: display_env(context); break;
        case 2: ENV->env = set_env(context, av[1], ""); break;
        case 3: ENV->env = set_env(context, av[1], av[2]); break;
        default:
            display_error(context, "setenv: Too many arguments.\n", NULL); break;
    }
    return ENV;
}
