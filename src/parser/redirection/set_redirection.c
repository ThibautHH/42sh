/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_redirection.c
*/

#include "mysh/redirection.h"

bool set_redirection(redirs_t *redirs, char *str, mysh_t *context)
{
    return set_redirection_output(redirs, str, context)
        || set_redirection_input(redirs, str, context);
}
