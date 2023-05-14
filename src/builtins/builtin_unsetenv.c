/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_unsetenv.c
*/

#include <stdio.h>

#include "mysh.h"

void builtin_unsetenv(mysh_t *context)
{
    if (CMDARGC < 2) {
        if (fputs("unsetenv: Too few arguments.\n", stderr) < 0)
            DIE;
        STATUS = 1;
        return;
    }
    for (size_t i = 1; CMDARGS[i]; i++)
        var_remove(context, CMDARGS[i], VAR_ENV);
    STATUS = 0;
}
