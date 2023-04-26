/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** print_alias
*/

#include "mysh.h"
#include "ice/printf.h"

bool print_alias(mysh_t *context, char *name)
{
    alias_t *alias;

    if (name == NULL) {
        TAILQ_FOREACH(alias, ALIASQ, entries) {
            ice_printf("%s\t", alias->name);
            ice_printf("%s\n", alias->value);
        }
        return true;
    }
    TAILQ_FOREACH(alias, ALIASQ, entries) {
        if (ice_strcmp(alias->name, name) == 0) {
            ice_printf("%s\n", alias->value);
            return true;
        }
    }
    return true;
}

    if (name == NULL) {
        TAILQ_FOREACH(alias, ALIASQ, entries) {
            ice_printf("%s\t", alias->name_buffer);
            print_alias_value(alias);
        }
        return true;
    }
    TAILQ_FOREACH(alias, ALIASQ, entries) {
        if (ice_strcmp(alias->name_buffer, name) == 0) {
            print_alias_value(alias);
            return true;
        }
    }
    return true;
}