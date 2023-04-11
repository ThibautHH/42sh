/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** mysh.c
*/

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>

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

static int mysh(char **global_env)
{
    env_t *env = load_env(global_env);

    if (!env)
        return 84;
    while (!env->exit)
        if (loop_input(env))
            return 84;
    return destroy_env(env);
}

int main(int ac, UNUSED char **av, char **env)
{
    return (ac == 1) ? mysh(env) : 84;
}
