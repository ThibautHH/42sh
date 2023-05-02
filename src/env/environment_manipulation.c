/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** environment_manipulation.c
*/

#include <stdlib.h>

#include "mysh.h"

static bool is_env_named(env_t *env, char *name)
{
    size_t nlen = ice_strlen(name);

    return (nlen == ice_strtil(ENVN(env), '='))
        && (!ice_strncmp2(ENVN(env), name, nlen));
}

env_t *env_get(mysh_t *context, char *name)
{
    env_t *env;

    TAILQ_FOREACH(env, ENVQ, entries)
        if (is_env_named(env, name))
            return env;
    return NULL;
}

void env_add(mysh_t *context, char *var)
{
    env_t *env = malloc(sizeof(env_t));

    if (!env)
        DIE;
    env->name = &(*ENVV(env)) - (ice_strtil(var, '=') + 1);
    ice_strcpy(ENVN(env), var);
    TAILQ_INSERT_TAIL(ENVQ, env, entries);
    ENVC++;
}

void env_update(mysh_t *context, char *name, char *value)
{
    env_t *env;

    TAILQ_FOREACH(env, ENVQ, entries)
        if (is_env_named(env, name)) {
            ice_strcpy(ENVV(env), value);
            return;
        }
    env = malloc(sizeof(env_t));
    if (!env)
        DIE;
    env->name = &(*ENVV(env)) - (ice_strlen(name) + 1);
    ice_strcpy(ENVN(env), name);
    ice_strcpy(ENVV(env), value);
    ENVV(env)[-1] = '=';
    TAILQ_INSERT_TAIL(ENVQ, env, entries);
    ENVC++;
}

void env_remove(mysh_t *context, char *name)
{
    env_t *env;
    env_t *tmp;

    TAILQ_FOREACH_SAFE(env, ENVQ, entries, tmp)
        if (is_env_named(env, name)) {
            TAILQ_REMOVE(ENVQ, env, entries);
            free(env);
            ENVC--;
            return;
        }
}
