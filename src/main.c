/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** mysh.c
*/

#include "mysh/env.h"
#include "mysh/parser.h"

static int mysh(char **global_env)
{
    env_t *env = load_env(global_env);

    return (env && !handle_input(env)) ? destroy_env(env) : 84;
}

int main(int ac, UNUSED char **av, char **env)
{
    return (ac == 1) ? mysh(env) : 84;
}
