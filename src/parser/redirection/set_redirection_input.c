/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** set_redirection_input.c
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "ice/output.h"
#include "ice/string.h"
#include "redirection.h"


static bool read_input(redir_t *redir, const char *str)
{
    size_t size = 0;
    char *line = NULL;
    int line_len;
    int str_len = (int)ice_strlen(str);

    while (true) {
        write(STDOUT_FILENO, "> ", 2);
        line_len = (int)getline(&line, &size, stdin);
        if (line_len == -1)
            return true;
        if (str_len == line_len - 1 && !ice_strncmp(line, str, str_len))
            break;
        if (write(redir->fd_in[1], line, line_len) < 0)
            return true;
    }
    free(line);
    return false;
}

bool get_input(redir_t *redir, const char *str)
{
    int pid;

    if (pipe(redir->fd_in) == -1)
        return true;
    pid = fork();
    if (pid == -1)
        return true;
    if (pid == 0) {
        close(redir->fd_in[0]);
        if (read_input(redir, str))
            exit(1);
        exit(0);
    } else {
        close(redir->fd_in[1]);
        redir->fd_in[1] = dup(STDIN_FILENO);
        dup2(redir->fd_in[0], STDIN_FILENO);
        redir->fd_in[0] = redir->fd_in[1];
        waitpid(pid, NULL, 0);
    }
    return false;
}

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
