/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** display_env.c
*/

#include "mysh.h"
#include "ice/printf.h"

bool display_env(char **env)
{
    for (ui_t i = 0; env[i]; i++)
        if (ice_printf("%s\n", env[i]) == -1)
            return true;
    return false;
}
