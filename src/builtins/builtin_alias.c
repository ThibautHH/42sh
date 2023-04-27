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
    for (int i = 0; i < 256; i ++)
        alias->name_buffer[i] = 0;
    for (int i = 0; i < 256; i ++)
        for (short unsigned int j = 0; j < 4096; j ++)
            alias->value[i][j] = 0;
}

static alias_t *fill_alias(char **av)
{
    alias_t *alias = malloc(sizeof(alias_t));
    int i = 0;

    wipe_alias(alias);
    ice_strcpy(alias->name_buffer, av[1]);
    for (av += 2; *av; av ++) {
        ice_strcpy(alias->value[i], *av);
        i ++;
    }
    return alias;
}

alias_t *search_for_alias(mysh_t *context, char *name)
{
    alias_t *alias;

    TAILQ_FOREACH(alias, ALIASQ, entries)
        if (ice_strcmp(alias->name_buffer, name) == 0)
            return alias;
    return NULL;
}

static bool rewrite_alias(alias_t *alias, char **av)
{
    int i = 0;

    wipe_alias(alias);
    ice_strcpy(alias->name_buffer, av[1]);
    for (av += 2; *av; av ++) {
        ice_strcpy(alias->value[i], *av);
        i ++;
    }
    return true;
}

bool builtin_alias(char **av, mysh_t *context)
{
    alias_t *alias;

    if (av[1] == NULL)
        return print_alias(context, NULL);
    if (av[2] == NULL)
        return print_alias(context, av[1]);
    if (is_alias_forbidden(av[1]) == true)
        return false;
    alias = search_for_alias(context, av[1]);
    if (alias != NULL)
        return rewrite_alias(alias, av);
    alias = fill_alias(av);
    TAILQ_INSERT_TAIL(ALIASQ, alias, entries);
    return true;
}
