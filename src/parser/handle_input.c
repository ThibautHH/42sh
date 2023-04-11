/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** handle_input.c
*/

#include <stdio.h>

#include "mysh.h"

bool handle_input(env_t *env)
{
    char *buffer;
    size_t size = 0;
    ssize_t len;

    while (!env->exit) {
        if (isatty(STDIN_FILENO)
            && (write(STDOUT_FILENO, "$> ", 3) < 0))
            return true;
        len = getline(&buffer, &size, stdin);
        if (len < 0)
            return isatty(STDIN_FILENO)
                && write(STDOUT_FILENO, "exit\n", 5) < 0;
        buffer[len - 1] = '\0';
        if (handle_sequence(buffer, env))
            return true;
    }
    return false;
}
