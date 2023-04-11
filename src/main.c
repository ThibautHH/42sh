/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** mysh.c
*/

#include "mysh.h"

static int mysh(char **global_env)
{
    env_t *env = load_env(global_env);

    return !env || handle_input(env) ? 84 : destroy_env(env);
}

int main(int ac, UNUSED char **av, char **env)
{
    return (ac == 1) ? mysh(env) : 84;
}
