/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_setenv.c
*/

#include "mysh/env.h"
#include "ice/array.h"
#include "mysh/miscellaneous.h"

env_t *builtin_setenv(char **av, env_t *env)
{
    ull_t av_len = ice_array_len((void **)av);

    switch (av_len) {
        case 1: display_env(env); break;
        case 2: env->env = set_env(env, av[1], ""); break;
        case 3: env->env = set_env(env, av[1], av[2]); break;
        default:
            display_error(env, "setenv: Too many arguments.\n", NULL); break;
    }
    return env;
}
