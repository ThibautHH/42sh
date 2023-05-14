/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** builtin_echo.c
*/

#include "mysh.h"

void builtin_echo(mysh_t *context)
{
    for (size_t i = 1; CMDARGS[i]; i++)
        PRINT(i > 1 ? " %s" : "%s", CMDARGS[i]);
    PRINT("\n");
    STATUS = 0;
}
