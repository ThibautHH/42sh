/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_env.c
*/

#include "ice/printf.h"

#include "mysh.h"

void builtin_env(mysh_t *context)
{
    env_t *env;
    TAILQ_FOREACH(env, ENVQ, entries)
        if (ice_printf("%s\n", env->name) < 0)
            DIE;
    STATUS = 0;
}
