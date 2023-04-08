/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** input.c
*/

#include <fcntl.h>
#include <stdlib.h>

#include "ice/output.h"
#include "redirection.h"

static bool handle_extract(redir_t *redir, char *str, bool read, bool input)
{
    if (read && input) {
        ice_puts("Ambiguous output redirect.\n");
        return false;
    }
    if (read)
        return extract_input(redir, str, "<");
    if (input)
        return extract_input(redir, str, "<<");
    return true;
}

static bool count_input(redir_t *redir, char *str)
{
    ui_t read = 0;
    ui_t input = 0;

    if (!str[0])
        return true;
    for (int i = 0; str[i + 1]; i++) {
        if (str[i] == '<' && str[i + 1] == '<') {
            input++;
            i++;
            redir->input = INPUT;
            continue;
        }
        if (str[i] == '<') {
            read++;
            redir->input = READ;
        }
    }
    return handle_extract(redir, str, read, input);
}

bool set_input(redir_t *redir, char *str, env_t *env)
{
    if (!count_input(redir, str))
        return true;
    if (!redir->file_in)
        return false;
    if (redir->input == INPUT)
        return get_input(redir, redir->file_in);
    redir->fd_in[0] = dup(STDIN_FILENO);
    if (redir->fd_in[0] == -1)
        return true;
    redir->fd_in[1] = open(redir->file_in, O_RDONLY);
    if (redir->fd_in[1] == -1 || dup2(redir->fd_in[1], STDIN_FILENO) == -1) {
        exit_env(env);
        return true;
    }
    return false;
}

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
