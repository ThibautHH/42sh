/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** dup_env.c
*/

#include <malloc.h>

#include "mysh.h"
#include "ice/string.h"

char **dup_env(mysh_t *context)
{
    char **env = malloc(sizeof(char *) * (ENVC + 1));
    if (!env)
        DIE;
    env[ENVC] = NULL;
    env_t *var; size_t i = 0;
    TAILQ_FOREACH(var, ENVQ, entries)
        env[i++] = ENVN(var);
    return env;
}
