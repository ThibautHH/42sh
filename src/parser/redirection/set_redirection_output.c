/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** set_redirection_output.c
*/

#include <fcntl.h>
#include <unistd.h>

#include "mysh/env.h"
#include "ice/output.h"
#include "mysh/redirection.h"

static bool handle_extract(redir_t *redir, char *str, bool add, bool append)
{
    if (add + append > 1) {
        ice_puts("Ambiguous output redirect.\n");
        return false;
    }
    if (add)
        return extract_output(redir, str, ">");
    if (append)
        return extract_output(redir, str, ">>");
    return true;
}

static bool count_output(redir_t *redir, char *str)
{
    ui_t add = 0;
    ui_t append = 0;

    if (!str[0])
        return true;
    for (int i = 0; str[i + 1]; i++) {
        if (str[i] == '>' && str[i + 1] == '>') {
            append++;
            i++;
            redir->output = APPEND;
            continue;
        }
        if (str[i] == '>') {
            add++;
            redir->output = ADD;
        }
    }
    return handle_extract(redir, str, add, append);
}

bool set_redirection_output(redir_t *redir, char *str, env_t *env)
{
    int flags = O_WRONLY | O_CREAT;

    if (!count_output(redir, str))
        return true;
    if (!redir->file_out)
        return false;
    flags |= (redir->output == ADD) ? O_TRUNC : O_APPEND;
    redir->fd_out[1] = open(redir->file_out, flags, 0644);
    if (redir->fd_out[1] == -1)
        return true;
    redir->fd_out[0] = dup(STDOUT_FILENO);
    if (redir->fd_out[0] == -1 || dup2(redir->fd_out[1], STDOUT_FILENO) == -1) {
        exit_env(env);
        return true;
    }
    return false;
}
