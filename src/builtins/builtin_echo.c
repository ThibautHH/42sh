/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** builtin_echo.c
*/

#include "mysh.h"

void builtin_echo(mysh_t *context)
{
    for (size_t i = 1; CMDARGS[i]; i++) {
        if (i > 1)
            DWRITE(STDOUT_FILENO, " ", 1);
        DWRITE(STDOUT_FILENO, CMDARGS[i], ice_strlen(CMDARGS[i]));
    }
    DWRITE(STDOUT_FILENO, "\n", 1);
    STATUS = 0;
}
