/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** unset_redirection_output.c
*/

#include <malloc.h>
#include <unistd.h>

#include "mysh/redirection.h"

bool unset_redirection_output(redir_t *redir)
{
    if (!redir->file_out)
        return false;
    if (dup2(redir->fd_out[0], STDOUT_FILENO) == -1)
        return true;
    close(redir->fd_out[0]);
    close(redir->fd_out[1]);
    free(redir->file_out);
    return false;
}
