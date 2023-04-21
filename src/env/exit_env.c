/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exit_env.c
*/

#include "mysh.h"

void exit_env(mysh_t *context)
{
    EXIT = true;
    STATUS = 84;
}
