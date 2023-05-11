/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias_error_gestion
*/

#include "mysh.h"
#include "ice/printf.h"

bool is_alias_forbidden(mysh_t *context, char *alias)
{
    char *name[2] = {"alias", "unalias"};

    if (ice_strcmp(alias, name[0]) == 0 ||
        ice_strcmp(alias, name[1]) == 0) {
        if (ice_dprintf(2, FORBIDDEN, alias) < 0)
            DIE;
        return true;
    }
    return false;
}
