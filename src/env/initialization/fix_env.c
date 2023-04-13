/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** fix_env.c
*/

#include <malloc.h>
#include <unistd.h>

#include "mysh.h"
#include "ice/array.h"
#include "ice/string.h"
#include "ice/printf.h"

static bool fix_pwd(char **new_env, ull_t *j)
{
    ull_t i = 0;
    char *pwd;

    for (; new_env[i] && ice_strncmp(new_env[i], "PWD=", 4); i++);
    if (new_env[i])
        return false;
    pwd = getcwd(NULL, 0);
    if (!pwd || chdir(pwd) == -1)
        return true;
    ice_asprintf(&new_env[*j] , "PWD=%s", pwd);
    if (!new_env[*j])
        return true;
    free(pwd);
    new_env[++(*j)] = NULL;
    return false;
}

static bool fix_path(char **new_env, ull_t *j)
{
    ull_t i = 0;

    for (; new_env[i] && ice_strncmp(new_env[i], "PATH=", 5); i++);
    if (new_env[i])
        return false;
    new_env[*j] = ice_strdup("PATH=/usr/bin");
    if (!new_env[*j])
        return true;
    new_env[++(*j)] = NULL;
    return false;
}

char **fix_env(char **env)
{
    ull_t j = 0;
    ull_t size = ice_array_len((void **)env);
    char **new_env = malloc(sizeof(char *) * (size + 4));

    if (!new_env)
        return NULL;
    for (ull_t i = 0 ; env[i] ; i++, j++)
        new_env[j] = env[i];
    free(env);
    new_env[j] = NULL;
    if (fix_pwd(new_env, &j) || fix_path(new_env, &j))
        return NULL;
    return new_env;
}
