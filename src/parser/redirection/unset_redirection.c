/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** unset_redirection.c
*/

#include "redirection.h"

bool unset_redirection(redir_t *redir)
{
    return unset_output(redir) || unset_input(redir);
}
