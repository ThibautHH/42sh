/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias_error_gestion
*/

#include <string.h>

#include "mysh.h"

bool is_alias_forbidden(mysh_t *context, char *alias)
{
    if (!strcmp(alias, "alias") || !strcmp(alias, "unalias")) {
        ERRPRINT("%s: Too dangerous to alias that.\n", alias);
        return true;
    }
    return false;
}
