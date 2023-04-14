/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unset_redirection_output.c
*/

#include <malloc.h>
#include <unistd.h>

#include "mysh/redirection.h"

bool unset_redirection_output(redirs_t *redirs)
{
    if (!redirs->file_out)
        return false;
    if (dup2(redirs->fd_out[0], STDOUT_FILENO) == -1)
        return true;
    close(redirs->fd_out[0]);
    close(redirs->fd_out[1]);
    free(redirs->file_out);
    return false;
}
