/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_exit.c
*/

#include "mysh.h"

void builtin_exit(mysh_t *context)
{
    char *endptr;

    if (CMDARGC > 2) {
        DWRITE(STDERR_FILENO, "exit: Expression Syntax.\n", 25);
        STATUS = 1;
        return;
    }
    EXIT = 1;
    if (CMDARGC == 2) {
        STATUS = strtol(CMDARGS[1], &endptr, 10);
        if (*endptr) {
            DWRITE(STDERR_FILENO, "exit: Badly formed number.\n", 27);
            STATUS = 1;
        }
    }
}
