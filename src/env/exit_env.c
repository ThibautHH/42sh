/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** exit_env.c
*/

#include "mysh.h"

void exit_env(env_t *env)
{
    env->exit = true;
    env->status = 84;
}
