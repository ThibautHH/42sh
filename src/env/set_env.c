/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** set_env.c
*/

#include <malloc.h>

#include "mysh.h"
#include "ice/array.h"
#include "ice/string.h"
#include "ice/printf.h"
#include "ice/output.h"

static bool name_is_allowed(const char *name)
{
    for (ull_t i = 0 ; name[i] ; i++)
        if (!IS_ALPHANUM(name[i]) && name[i] != '_')
            return true;
    return false;
}

char **update_env(char **env, char *name, char *value)
{
    ull_t i = 0;
    ull_t len = ice_strlen(name);
    char **new_env = malloc(sizeof(char *) * (ice_array_len((void **)env) + 2));

    if (!new_env)
        return NULL;
    for (; env[i] && ice_strncmp(env[i], name, len) ; i++)
        new_env[i] = env[i];
    free(env[i]);
    ice_asprintf(&new_env[i], "%s=%s", name, value);
    if (!new_env[i])
        return NULL;
    if (env[i++])
        for (; env[i] ; i++)
            new_env[i] = env[i];
    new_env[i] = NULL;
    free(env);
    return new_env;
}

char **set_env(env_t *env, char *name, char *value)
{
    if (name_is_allowed(name)) {
        ice_puts("setenv: Variable name must "
            "contain alphanumeric characters.\n");
        env->status = 1;
        return env->env;
    }
    return update_env(env->env, name, value);
}
