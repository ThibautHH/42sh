/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** destroy_alias
*/

#include <malloc.h>

#include "mysh.h"
#include "ice/array.h"

void destroy_alias(mysh_t *context)
{
    alias_t *alias, *tmp;

    TAILQ_FOREACH_SAFE(alias, ALIASQ, entries, tmp) {
        TAILQ_REMOVE(ALIASQ, alias, entries);
        free(alias);
    }
}
