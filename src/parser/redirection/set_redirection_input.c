/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_redirection_input.c
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "mysh.h"
#include "ice/output.h"
#include "ice/string.h"
#include "mysh/redirection.h"

static bool read_input(redirs_t *redirs, const char *str)
{
    size_t size = 0;
    char *line = NULL;
    int line_len;
    int str_len = (int)ice_strlen(str);

    while (true) {
        if (isatty(STDIN_FILENO) && write(STDOUT_FILENO, "? ", 2) < 0)
            return true;
        line_len = (int)getline(&line, &size, stdin);
        if (line_len == -1)
            return true;
        if (str_len == line_len - 1 && !ice_strncmp(line, str, str_len))
            break;
        if (write(redirs->fd_in[1], line, line_len) < 0)
            return true;
    }
    free(line);
    return false;
}

static bool get_input(redirs_t *redirs, const char *str)
{
    int pid;

    if (pipe(redirs->fd_in) == -1)
        return true;
    pid = fork();
    if (pid == -1)
        return true;
    if (pid == 0) {
        close(redirs->fd_in[0]);
        if (read_input(redirs, str))
            exit(1);
        exit(0);
    } else {
        close(redirs->fd_in[1]);
        redirs->fd_in[1] = dup(STDIN_FILENO);
        dup2(redirs->fd_in[0], STDIN_FILENO);
        redirs->fd_in[0] = redirs->fd_in[1];
        waitpid(pid, NULL, 0);
    }
    return false;
}

static bool handle_extract(redirs_t *redirs, char *str, bool read, bool input)
{
    if (read && input) {
        ice_puts("Ambiguous output redirect.\n");
        return false;
    }
    if (read)
        return extract_input(redirs, str, "<");
    if (input)
        return extract_input(redirs, str, "<<");
    return true;
}

static bool count_input(redirs_t *redirs, char *str)
{
    ui_t read = 0;
    ui_t input = 0;

    if (!str[0])
        return true;
    for (int i = 0; str[i + 1]; i++) {
        if (str[i] == '<' && str[i + 1] == '<') {
            input++;
            i++;
            redirs->input = INPUT;
            continue;
        }
        if (str[i] == '<') {
            read++;
            redirs->input = READ;
        }
    }
    return handle_extract(redirs, str, read, input);
}

bool set_redirection_input(redirs_t *redirs, char *str, mysh_t *context)
{
    if (!count_input(redirs, str))
        return true;
    if (!redirs->file_in)
        return false;
    if (redirs->input == INPUT)
        return get_input(redirs, redirs->file_in);
    redirs->fd_in[0] = dup(STDIN_FILENO);
    if (redirs->fd_in[0] == -1)
        return true;
    redirs->fd_in[1] = open(redirs->file_in, O_RDONLY);
    if (redirs->fd_in[1] == -1 || dup2(redirs->fd_in[1], STDIN_FILENO) == -1)
        DIE;
    return false;
}
