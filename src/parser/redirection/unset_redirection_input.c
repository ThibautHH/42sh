/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unset_redirection_input.c
*/

#include <malloc.h>
#include <unistd.h>

#include "mysh/redirection.h"

bool unset_redirection_input(redirs_t *redirs)
{
    if (!redirs->file_in)
        return false;
    if (dup2(redirs->fd_in[0], STDIN_FILENO) == -1)
        return true;
    close(redirs->fd_in[0]);
    close(redirs->fd_in[1]);
    free(redirs->file_in);
    return false;
}
