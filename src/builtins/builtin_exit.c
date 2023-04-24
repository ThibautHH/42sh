/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_exit.c
*/

#include <unistd.h>

#include "ice/array.h"
#include "ice/int.h"

#include "mysh.h"
#include "mysh/parsing.h"

bool builtin_exit(mysh_t *context)
{
    if (CMDARGC > 2) {
        DWRITE(STDERR_FILENO, "exit: Expression Syntax.\n", 25);
        return (STATUS = 1);
    }
    STATUS = CMDARGC == 2 ? ice_atoi(CMDARGS[1]) : STATUS;
    EXIT = 1;
    return false;
}
