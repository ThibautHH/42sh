/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** buitlin_exit.c
*/

#include <unistd.h>

#include "mysh.h"

env_t *builtin_exit(UNUSED char **av, env_t *env)
{
    if (write(1, "exit\n", 5) < 0)
        return env;
    env->exit = true;
    env->status = 0;
    return env;
}
