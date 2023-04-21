/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** display_env.c
*/

#include "mysh/env.h"
#include "ice/printf.h"

bool display_env(mysh_t *context)
{
    for (ui_t i = 0; ENV->env[i]; i++)
        if (ice_printf("%s\n", ENV->env[i]) == -1)
            return true;
    return false;
}
