/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unalias
*/

#include "mysh.h"

#include <stdlib.h>

bool builtin_unalias(char **av, mysh_t *context)
{
    alias_t *alias;

    for (int i = 1; av[i] != NULL; i ++) {
        alias = search_for_alias(context, av[i]);
        if (alias != NULL) {
            TAILQ_REMOVE(ALIASQ, alias, entries);
            free(alias);
        }
    }
    return true;
}
