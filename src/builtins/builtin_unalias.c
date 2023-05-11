/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unalias
*/

#include "mysh.h"

#include <stdlib.h>

void builtin_unalias(struct mysh_s *context)
{
    alias_t *alias;

    for (int i = 1; CMDARGS[i] != NULL; i ++) {
        alias = search_for_alias(context, CMDARGS[i]);
        if (alias != NULL) {
            TAILQ_REMOVE(ALIASQ, alias, entries);
            free(alias);
        }
    }
}
