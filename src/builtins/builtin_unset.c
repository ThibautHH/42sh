/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_unsetenv.c
*/

#include "mysh.h"

void builtin_unset(mysh_t *context)
{
    if (CMDARGC < 2) {
        DWRITE(STDERR_FILENO, "unsetenv: Too few arguments.\n", 29);
        STATUS = 1;
        return;
    }
    for (size_t i = 1; CMDARGS[i]; i++)
        var_remove(context, CMDARGS[i], VAR_SHELL);
    STATUS = 0;
}
