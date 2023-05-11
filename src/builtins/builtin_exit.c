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

void builtin_exit(mysh_t *context)
{
    if (CMDARGC > 2) {
        DWRITE(STDERR_FILENO, "exit: Expression Syntax.\n", 25);
        STATUS = 1;
        return;
    }
    EXIT = 1;
    if (CMDARGC == 2)
        STATUS = ice_atoi(CMDARGS[1]);
}
