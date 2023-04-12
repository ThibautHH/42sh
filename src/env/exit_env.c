/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exit_env.c
*/

#include "mysh.h"

void exit_env(env_t *env)
{
    env->exit = true;
    env->status = 84;
}
