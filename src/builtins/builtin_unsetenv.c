/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_unsetenv.c
*/

#include "ice/array.h"

#include "mysh/parsing.h"
#include "mysh/miscellaneous.h"

void builtin_unsetenv(mysh_t *context)
{
    if (CMDARGC != 2) {
        if (CMDARGC < 2) {
            DWRITE(STDERR_FILENO, "unsetenv: Too few arguments.\n", 29);
        } else
            DWRITE(STDERR_FILENO, "unsetenv: Too many arguments.\n", 30);
        STATUS = 1;
        return;
    }
    env_remove(context, CMDARGS[1]);
    STATUS = 0;
}
