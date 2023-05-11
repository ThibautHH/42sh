/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** print_alias
*/

#include "mysh.h"

#include <stdio.h>

bool print_alias(mysh_t *context, char *name)
{
    alias_t *alias;

    if (name == NULL) {
        TAILQ_FOREACH(alias, ALIASQ, entries) {
            if (printf("%s\t", alias->name) < 0
                || printf("%s\n", alias->value) < 0)
                DIE;
        }
        return true;
    }
    TAILQ_FOREACH(alias, ALIASQ, entries) {
        if (ice_strcmp(alias->name, name) == 0) {
            if (printf("%s\n", alias->value) < 0)
                DIE;
            return true;
        }
    }
    return true;
}
