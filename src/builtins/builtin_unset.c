/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_unsetenv.c
*/

#include <stdio.h>

#include "mysh.h"

static void write_error(mysh_t *context, char *error)
{
    if (fputs(error, stderr) < 0)
        DIE;
    STATUS = 1;
}

void builtin_unset(mysh_t *context)
{
    if (CMDARGC < 2) {
        write_error(context, "unset: Too few arguments.\n");
        return;
    }
    for (size_t i = 1; CMDARGS[i]; i++)
        var_remove(context, CMDARGS[i], VAR_SHELL);
    STATUS = 0;
}
