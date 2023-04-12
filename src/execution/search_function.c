/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** search_binary_function.c
*/

#include <malloc.h>
#include <unistd.h>

#include "mysh.h"
#include "ice/array.h"
#include "ice/string.h"
#include "ice/printf.h"
#include "mysh/builtins.h"

static bool command_not_found(char *cmd, env_t *env)
{
    ice_printf("%s: Command not found.\n", cmd);
    env->status = 1;
    return false;
}

static char **get_path(char **env)
{
    ull_t i = 0;

    for (; env[i] && ice_strncmp(env[i], "PATH=", 5); i++);
    if (!env[i])
        return NULL;
    return ice_strsplit(env[i] + 5, ":");
}

static char *search_in_path(char **av, env_t *env)
{
    char *binary;
    char **path = get_path(env->env);

    for (ull_t i = 0; path[i]; i++) {
        ice_asprintf(&binary, "%s/%s", path[i], av[0]);
        if (!access(binary, F_OK)) {
            ice_free_array((void **)path);
            return binary;
        }
        free(binary);
    }
    ice_free_array((void **)path);
    if (!access(av[0], F_OK))
        return ice_strdup(av[0]);
    return NULL;
}

static bool builtin_function(char **av, env_t **env)
{
    for (ui_t i = 0; builtins[i].name; i++)
        if (ice_strcmp(builtins[i].name, av[0]) == 0) {
            *env = builtins[i].func(av, *env);
            return false;
        }
    return true;
}

bool search_function(char **av, env_t *env)
{
    char *binary = search_in_path(av, env);

    if (!av[0]) {
        env->status = 0;
        return false;
    }
    if (!builtin_function(av, &env))
        return false;
    if (!binary)
        return command_not_found(av[0], env);
    if (execute_binary(binary, av, env))
        return true;
    free(binary);
    return false;
}
