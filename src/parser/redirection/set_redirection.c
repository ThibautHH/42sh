/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** set_redirection.c
*/

#include "mysh/redirection.h"

bool set_redirection(redir_t *redir, char *str, env_t *env)
{
    return set_redirection_output(redir, str, env)
        || set_redirection_input(redir, str, env);
}
