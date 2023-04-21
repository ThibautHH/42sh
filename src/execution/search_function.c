/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** search_binary_function.c
*/

#include <malloc.h>
#include <unistd.h>

#include "ice/array.h"
#include "ice/string.h"
#include "ice/printf.h"
#include "mysh/execution.h"
#include "mysh/builtins.h"
#include "mysh/env.h"

static bool command_not_found(char *cmd, mysh_t *context)
{
    ice_printf("%s: Command not found.\n", cmd);
    STATUS = 1;
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

static char *search_in_path(char **av, mysh_t *context)
{
    char *binary;
    char **path = get_path(ENV->env);

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

static bool builtin_function(char **av, mysh_t *context)
{
    for (ui_t i = 0; builtins[i].name; i++)
        if (ice_strcmp(builtins[i].name, av[0]) == 0) {
            ENV = builtins[i].func(av, context);
            return false;
        }
    return true;
}

bool search_function(char **av, mysh_t *context)
{
    char *binary = search_in_path(av, context);

    if (!av[0]) {
        STATUS = 0;
        return false;
    }
    if (!builtin_function(av, context))
        return false;
    if (!binary)
        return command_not_found(av[0], context);
    if (execute_binary(binary, av, context))
        return true;
    free(binary);
    return false;
}
