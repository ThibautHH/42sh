/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias_substitution
*/

#include "mysh.h"

#include <string.h>
#include <stdio.h>

static alias_t *preshot_alias(mysh_t *, char *, char *, size_t);

static char *swap_line(char *line, char *alias, int i, int alias_name_len)
{
    int len = ice_strlen(line) + ice_strlen(alias) - alias_name_len;
    char *newline = malloc(sizeof(char) * (len + 1));

    if (!newline)
        return NULL;
    for (int i = 0; i <= len; i++)
        newline[i] = 0;
    newline = ice_strncpy2(newline, line, i);
    line += alias_name_len + i;
    ice_strcat(newline, alias);
    ice_strcat(newline, line);
    line -= (alias_name_len + i);
    ice_strcpy(line, newline);
    free(newline);
    return line;
}

static alias_t *is_loop(mysh_t *context, alias_t *alias,
    char *old_name, size_t rec)
{
    if (strcmp(old_name, alias->value) == 0 || rec > context->alias.count) {
        if (dprintf(2, "Alias loop.\n") < 0)
            DIE;
        return NULL;
    }
    return preshot_alias(context, alias->name, alias->value, rec + 1);
}

static alias_t *preshot_alias(mysh_t *context, char *old_name,
    char *old_value, size_t rec)
{
    alias_t *alias;

    TAILQ_FOREACH(alias, ALIASQ, entries)
        if (strcmp(old_value, alias->name) == 0)
            return is_loop(context, alias, old_name, rec);
    TAILQ_FOREACH(alias, ALIASQ, entries) {
        if (strcmp(old_name, alias->name) == 0) {
            return alias;
        }
    }
    return NULL;
}

static _Bool aliasing(mysh_t *context, int off)
{
    alias_t *alias;
    int alias_name_len = 0;

    TAILQ_FOREACH(alias, ALIASQ, entries) {
        if (strncmp(alias->name, LINE + off, ice_strlen(alias->name)) == 0
            && (LINE[off + ice_strlen(alias->name)] == ' '
            || LINE[off + ice_strlen(alias->name)] == '\n')) {
            alias_name_len = ice_strlen(alias->name);
            alias = preshot_alias(context, alias->name, alias->value, 0);
            if (alias == NULL)
                return false;
            LINE = swap_line(LINE, alias->value, off, alias_name_len);
            return true;
        }
    }
    return true;
}

_Bool substitute_alias(mysh_t *context)
{
    _Bool separator = false;

    P = LINE;
    for (int i = 0; P[i] != '\0'; i++) {
        if (i != 0 && (P[i - 1] == '|' || P[i - 1] == ';'
            || (i > 1 && ((P[i - 2] == '&' && P[i - 1] == '&')
            || (P[i - 2] == '|' && P[i - 1] == '|')))))
            separator = true;
        if ((i == 0 || separator) && aliasing(context, i) == false) {
            STATUS = 1;
            return false;
        }
        if (LINE[i] != ' ')
            separator = false;
    }
    return true;
}
