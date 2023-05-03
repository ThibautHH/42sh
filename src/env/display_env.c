/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** display_env.c
*/

#include "mysh.h"
#include "ice/printf.h"

void display_env(mysh_t *context)
{
    env_t *env;
    TAILQ_FOREACH(env, ENVQ, entries)
        if (ice_printf("%s\n", env->name) < 0)
            DIE;
}
