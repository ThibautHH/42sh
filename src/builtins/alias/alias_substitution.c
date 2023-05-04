/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias_substitution
*/

#include "mysh.h"

static char *swap_line(char *line, char *alias, int i, int alias_name_len)
{
    int len = ice_strlen(line) + ice_strlen(alias) - alias_name_len;
    char *newline = malloc(sizeof(char) * (len + 1));
    char *line_tmp = NULL;

    for (int i = 0; i <= len; i ++)
        newline[i] = 0;
    newline = ice_strncpy2(newline, line, i);
    line += alias_name_len + i;
    ice_strcat(newline, alias);
    ice_strcat(newline, line);
    line -= (alias_name_len + i);
    line = realloc(line_tmp, sizeof(char) * (len + 1));
    ice_strcpy(line, newline);
    free(newline);
    return line;
}

static _Bool is_alias(mysh_t *context, int off)
{
    alias_t *alias;

    TAILQ_FOREACH(alias, ALIASQ, entries) {
        if (ice_strncmp2(alias->name, LINE + off, ice_strlen(alias->name)) == 0
        && (LINE[off + ice_strlen(alias->name)] == ' '
        || LINE[off + ice_strlen(alias->name)] == '\n')) {
            LINE = swap_line(LINE, alias->value, off, ice_strlen(alias->name));
            return true;
        }
    }
    return false;
}

_Bool substitute_alias(mysh_t *context)
{
    int pipe = 0;

    for (int i = 0; LINE[i] != '\0'; i++) {
        if (LINE[i - 1] == '|' || LINE[i - 1] == ';')
            pipe = 1;
        if ((i == 0 || pipe == 1) && is_alias(context, i) == true)
            continue;
        if (LINE[i] != ' ')
            pipe = 0;
    }
    return true;
}
