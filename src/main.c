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

bool handle_sequence(char *buffer, env_t *env)
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

static int mysh(char **global_env)
{
    env_t *env = load_env(global_env);

    return !env || handle_input(env) ? 84 : destroy_env(env);
}

int main(int ac, UNUSED char **av, char **env)
{
    return (ac == 1) ? mysh(env) : 84;
}
