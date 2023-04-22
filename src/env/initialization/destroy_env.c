/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** destroy_env.c
*/

#include <malloc.h>

#include "mysh.h"
#include "ice/array.h"

void destroy_env(mysh_t *context)
{
    env_t *env, *tmp;
    TAILQ_FOREACH_SAFE(env, ENVQ, entries, tmp) {
        TAILQ_REMOVE(ENVQ, env, entries);
        free(env);
    }
}
