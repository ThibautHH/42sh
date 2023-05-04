/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_alias
** the aliases are stored in a linked list as char **
** av[0] = name of the alias
** av[1, ...] = substitution
*/

#include "mysh.h"

#include <stdlib.h>

static void wipe_alias(alias_t *alias)
{
    for (int i = 0; i < 4096; i ++)
        alias->name[i] = 0;
    for (int i = 0; i < 32768; i ++)
        alias->value[i] = 0;
}

static alias_t *fill_alias(char **av)
{
    alias_t *alias = malloc(sizeof(alias_t));

    wipe_alias(alias);
    ice_strcpy(alias->name, av[1]);
    for (av += 2; *av; av ++) {
        ice_strcat(alias->value, *av);
        if (av[1] != NULL)
            ice_strcat(alias->value, " ");
    }
    return alias;
}

alias_t *search_for_alias(mysh_t *context, char *name)
{
    alias_t *alias;

    TAILQ_FOREACH(alias, ALIASQ, entries)
        if (ice_strcmp(alias->name, name) == 0)
            return alias;
    return NULL;
}

static void rewrite_alias(alias_t *alias, char **av)
{
    wipe_alias(alias);
    ice_strcpy(alias->name, av[1]);
    for (av += 2; *av; av ++) {
        ice_strcat(alias->value, *av);
        if (av[1] != NULL)
            ice_strcat(alias->value, " ");
    }
}

void builtin_alias(mysh_t *context)
{
    alias_t *alias;

    if (CMDARGS[1] == NULL) {
        print_alias(context, NULL);
        return;
    } else if (CMDARGS[2] == NULL) {
        print_alias(context, CMDARGS[1]);
        return;
    }
    if (is_alias_forbidden(CMDARGS[1]) == true) {
        STATUS = 1;
        return;
    }
    alias = search_for_alias(context, CMDARGS[1]);
    if (alias != NULL) {
        rewrite_alias(alias, CMDARGS);
        return;
    }
    alias = fill_alias(CMDARGS);
    TAILQ_INSERT_TAIL(ALIASQ, alias, entries);
}
