/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** redirection.c
*/

#include <stdbool.h>

#include "mysh.h"
#include "redirection.h"

bool set_redirection(redir_t *redir, char *str, env_t *env)
{
    return set_output(redir, str, env) || set_input(redir, str, env);
}

bool unset_redirection(redir_t *redir)
{
    return unset_output(redir) || unset_input(redir);
}
