/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_exit.c
*/

#include <unistd.h>

#include "mysh.h"

env_t *builtin_exit(UNUSED char **av, mysh_t *context)
{
    EXIT = true;
    STATUS = 0;
    return ENV;
}
