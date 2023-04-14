/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_redirection.c
*/

#include "mysh/redirection.h"

bool set_redirection(redirs_t *redirs, char *str, env_t *env)
{
    return set_redirection_output(redirs, str, env)
        || set_redirection_input(redirs, str, env);
}
