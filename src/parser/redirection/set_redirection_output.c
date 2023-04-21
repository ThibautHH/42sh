/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_redirection_output.c
*/

#include <fcntl.h>
#include <unistd.h>

#include "mysh/env.h"
#include "ice/output.h"
#include "mysh/redirection.h"

static bool handle_extract(redirs_t *redirs, char *str, bool add, bool append)
{
    if (add + append > 1) {
        ice_puts("Ambiguous output redirect.\n");
        return false;
    }
    if (add)
        return extract_output(redirs, str, ">");
    if (append)
        return extract_output(redirs, str, ">>");
    return true;
}

static bool count_output(redirs_t *redirs, char *str)
{
    ui_t add = 0;
    ui_t append = 0;

    if (!str[0])
        return true;
    for (int i = 0; str[i + 1]; i++) {
        if (str[i] == '>' && str[i + 1] == '>') {
            append++;
            i++;
            redirs->output = APPEND;
            continue;
        }
        if (str[i] == '>') {
            add++;
            redirs->output = ADD;
        }
    }
    return handle_extract(redirs, str, add, append);
}

bool set_redirection_output(redirs_t *redirs, char *str, mysh_t *context)
{
    int flags = O_WRONLY | O_CREAT;

    if (!count_output(redirs, str))
        return true;
    if (!redirs->file_out)
        return false;
    flags |= (redirs->output == ADD) ? O_TRUNC : O_APPEND;
    redirs->fd_out[1] = open(redirs->file_out, flags, 0644);
    if (redirs->fd_out[1] == -1)
        return true;
    redirs->fd_out[0] = dup(STDOUT_FILENO);
    if (redirs->fd_out[0] == -1
        || dup2(redirs->fd_out[1], STDOUT_FILENO) == -1) {
        exit_env(context);
        return true;
    }
    return false;
}
