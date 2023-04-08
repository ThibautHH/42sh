/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** get_input.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
