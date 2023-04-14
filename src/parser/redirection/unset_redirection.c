/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unset_redirection.c
*/

#include "mysh/redirection.h"

bool unset_redirection(redirs_t *redirs)
{
    return unset_redirection_output(redirs)
        || unset_redirection_input(redirs);
}
