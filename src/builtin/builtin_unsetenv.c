/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** builtin_unsetenv.c
*/

#include "mysh.h"

env_t *builtin_unsetenv(char **av, env_t *env)
{
    if (!av[1]) {
        display_error(env, "unsetenv: Too few arguments.\n", NULL);
        return env;
    }
    for (ull_t i = 1; av[i]; i++)
        env->env = unset_env(env->env, av[i]);
    return env;
}
