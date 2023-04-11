/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** mysh.c
*/

#include <stdio.h>
#include <unistd.h>

#include "mysh.h"
#include "list.h"
#include "ice/array.h"
#include "ice/string.h"
#include "redirection.h"

static bool handle_input(char *buffer, env_t *env)
{
    char **sequence = ice_strsplit(buffer, ";");

    if (!sequence)
        return true;
    for (int i = 0; sequence[i]; i++)
        if (handle_pipe(env, sequence[i]))
            return true;
    ice_free_array((void **)sequence);
    return false;
}

static bool loop_input(env_t *env)
{
    char *buffer;
    size_t size = 0;

    if (isatty(STDIN_FILENO)
        && (write(STDOUT_FILENO, "$> ", 3) == -1))
        return true;
    if (getline(&buffer, &size, stdin) == -1) {
        if (isatty(STDIN_FILENO)
            && write(STDOUT_FILENO, "exit\n", 5) == -1)
            return true;
        env->exit = true;
        return false;
    }
    buffer[ice_strlen(buffer) - 1] = '\0';
    return handle_input(buffer, env);
}

static bool loop_env(env_t *env)
{
    while (!env->exit)
        if (loop_input(env))
            return true;
    return false;
}

static int mysh(char **env)
{
    env_t st_env = {0};

    st_env.env = dup_env(env);
    if (!st_env.env)
        return 84;
    st_env.env = fix_env(st_env.env);
    if (!st_env.env || loop_env(&st_env))
        return 84;
    ice_free_array((void **)st_env.env);
    return st_env.status;
}

int main(int ac, UNUSED char **av, char **env)
{
    return (ac == 1) ? mysh(env) : 84;
}
