/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** unset_redirection_input.c
*/

#include <malloc.h>

#include "redirection.h"

bool unset_input(redir_t *redir)
{
    if (!redir->file_in)
        return false;
    if (dup2(redir->fd_in[0], STDIN_FILENO) == -1)
        return true;
    close(redir->fd_in[0]);
    close(redir->fd_in[1]);
    free(redir->file_in);
    return false;
}
