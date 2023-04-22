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

bool builtin_exit(char **av, mysh_t *context)
{
    size_t argc = ice_array_len((void **) av);
    if (argc > 2) {
        DWRITE(STDERR_FILENO, "exit: Expression Syntax.\n", 25);
        return (STATUS = 1);
    }
    STATUS = argc == 2 ? ice_atoi(av[1]) : STATUS;
    EXIT = 1;
    return false;
}
