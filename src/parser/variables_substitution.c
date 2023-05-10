/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** substitute_variables
*/

#include "mysh.h"
#include "mysh/commands.h"
#include "mysh/parsing.h"
#include "mysh/parsing_functions.h"

#include <string.h>
#include <stdio.h>

char *sub_variable(int var_len, char *value, int off, char *line)
{
    int len = strlen(line) - (var_len + 1) + strlen(value);
    char *newline = malloc(sizeof(char) * (len + 1));
    
    if (newline == NULL)
        return NULL;
    for (int i = 0; i <= len; i++)
        newline[i] = 0;
    newline = ice_strncpy2(newline, line, off);
    line += off + var_len + 1;
    ice_strcat(newline, value);
    ice_strcat(newline, line);
    line -= off + var_len + 1;
    ice_strcpy(line, newline);
    free(newline);
    return line;
}

_Bool variable_exist(mysh_t *context, int off, int len)
{
    var_t *var;
    var_type_t type = VAR_ENV;
    char variable[len];

    strncpy(variable, LINE + off, len);
    TAILQ_FOREACH(var, VARQ, entries) {
        if (strncmp(var->name, variable, len) == 0) {
            LINE = sub_variable(len, var->name + len + 1, off - 1, LINE);
            return true;
        }
    }
    dprintf(2, "%s: not found\n", variable);
    return false;
}

_Bool search_end(mysh_t *context, int off)
{
    for (int i = off + 1; LINE[i] != '\0'; i++) {
        if (LINE[i] == '}')
            return true;
        if (!IS_ALPHANUM(LINE[i])) {
            dprintf(2, "Missing '}'\n");
            return false;
        }
    }
    return false;
}

_Bool handle_curly(mysh_t *context)
{
    P = LINE;
    for (int i = 0; LINE[i] != '\0'; i++) {
        if (LINE[i] == '{')
            P += i + 1;
            if (!IS_SEPARATOR && *P != '\n' && search_end(context, i) == false)
                return false;
    }
    return true;
}

_Bool handle_variable(mysh_t *context, int off)
{
    int len = 0;

    for (; IS_ALPHANUM(LINE[off + len + 1]); len++);
    if (variable_exist(context, off + 1, len))
        return true;
    return false;
}

_Bool substitute_variables(mysh_t *context)
{
    P = LINE;
    if (handle_curly(context) == false)
        return false;
    for (int i = 0; LINE[i] != '\0'; i++) {
        if (LINE[i] == '$') {
            P += i + 1;
            if (!IS_SEPARATOR && P != '\n')
                return handle_variable(context, i);
            P -= i + 1;
        }
    }
    return true;
}
