/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unset_redirection.c
*/

#include "mysh/redirection.h"

bool unset_redirection(redir_t *redir)
{
    return unset_redirection_output(redir)
        || unset_redirection_input(redir);
}
