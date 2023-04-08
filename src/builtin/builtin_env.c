/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** builtins_env.c
*/

#include "mysh.h"

env_t *builtin_env(UNUSED char **av, env_t *env)
{
    display_env(env->env);
    return env;
}
