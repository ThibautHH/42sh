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

    if (isatty(STDIN_FILENO) && (write(STDOUT_FILENO, "$> ", 3) < 0))
        return true;
    len = getline(&buffer, &size, stdin);
    if (len < 0) {
        if (isatty(STDIN_FILENO) && write(STDOUT_FILENO, "exit\n", 5) < 0)
            return true;
        env->exit = true;
        return false;
    }
    buffer[len - 1] = '\0';
    return handle_sequence(buffer, env);
}
