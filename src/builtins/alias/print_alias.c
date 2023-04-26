/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** print_alias
*/

#include "mysh.h"
#include "ice/printf.h"

static void print_alias_value(alias_t *alias)
{
    for (int i = 0; alias->value[i][0] != 0 && i < 256; i ++) {
        ice_printf("%s", alias->value[i]);
        if (alias->value[i + 1][0] == 0) {
            ice_printf("\n");
            break;
        }
        ice_printf(" ");
    }
}

bool print_alias(mysh_t *context, char *name)
{
    alias_t *alias;

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
