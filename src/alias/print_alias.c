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
        TAILQ_FOREACH(alias, ALIASQ, entries)
            PRINT("%s\t%s\n", alias->name, alias->value);
        return true;
    }
    TAILQ_FOREACH(alias, ALIASQ, entries) {
        if (ice_strcmp(alias->name, name) == 0) {
            PRINT("%s\n", alias->value);
            return true;
        }
    }
    return true;
}
