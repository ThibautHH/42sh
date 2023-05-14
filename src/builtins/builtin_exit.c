/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_exit.c
*/

#include "mysh.h"

void builtin_exit(mysh_t *context)
{
    if (CMDARGC > 2) {
        DWRITE(STDERR_FILENO, "exit: Expression Syntax.\n", 25);
        STATUS = 1;
        return;
    }
    EXIT = 1;
    if (CMDARGC == 2)
        STATUS = atoi(CMDARGS[1]);
}
