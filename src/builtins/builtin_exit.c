/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_exit.c
*/

#include <stdio.h>

#include "mysh.h"

void builtin_exit(mysh_t *context)
{
    char *endptr;

    if (CMDARGC > 2) {
        ERRPRINT("exit: Expression Syntax.\n");
        STATUS = 1;
        return;
    }
    EXIT = 1;
    if (CMDARGC == 2) {
        STATUS = strtol(CMDARGS[1], &endptr, 10);
        if (*endptr) {
            ERRPRINT("exit: Badly formed number.\n");
            STATUS = 1;
        }
    }
}
