/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** prompt.c
*/

#include <unistd.h>

#include "mysh.h"

void prompt(UNUSED mysh_t *context)
{
    TTY_WRITE("$> ", 3);
}
