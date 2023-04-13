/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_input.c
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "mysh/parser.h"

bool handle_input(env_t *env)
{
    char *buffer;
    size_t size = 0;
    ssize_t len;

    while (!env->exit) {
        if (isatty(STDIN_FILENO)
            && (write(STDOUT_FILENO, "$> ", 3) < 0))
            return true;
        errno = 0;
        len = getline(&buffer, &size, stdin);
        if (len < 0)
            return (errno == 0) ? isatty(STDIN_FILENO)
                && write(STDOUT_FILENO, "exit\n", 5) < 0 : true;
        buffer[len - 1] = '\0';
        if (handle_sequence(buffer, env))
            return true;
    }
    return false;
}
