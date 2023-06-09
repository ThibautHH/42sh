/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unalias
*/

#include <malloc.h>

#include "mysh.h"

void builtin_unalias(struct mysh_s *context)
{
    alias_t *alias;

    for (int i = 1; CMDARGS[i]; i ++) {
        alias = search_for_alias(context, CMDARGS[i]);
        if (alias) {
            TAILQ_REMOVE(ALIASQ, alias, entries);
            free(alias);
        }
    }
}
