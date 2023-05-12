/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** substitute_variables
*/

#include <stdio.h>
#include <string.h>

#include "mysh/parsing_functions.h"

static char *sub_variable(int var_len, char *value, int off, char *line)
{
    int len = strlen(line) - (var_len + 1) + strlen(value);
    char *newline = malloc(sizeof(char) * (len + 1));

    if (newline == NULL)
        return NULL;
    for (int i = 0; i <= len; i++)
        newline[i] = 0;
    newline = ice_strncpy2(newline, line, off);
    line += off + var_len + 1;
    if (*line == '}') {
        line++;
        off++;
    }
    ice_strcat(newline, value);
    ice_strcat(newline, line);
    line -= off + var_len + 1;
    ice_strcpy(line, newline);
    free(newline);
    return line;
}

static bool exist_in_shell_var(mysh_t *context, int off, int curly,
    char *variable)
{
    var_t *var;
    var_type_t type = VAR_SHELL;
    int len = strlen(variable);

    TAILQ_FOREACH(var, VARQ, entries) {
        if (strncmp(var->name, variable, len) == 0) {
            LINE = sub_variable(len + curly, var->name + len + 1, off, LINE);
            return true;
        }
    }
    return false;
}

static bool variable_exist(mysh_t *context, int off, int len, int curly)
{
    var_t *var;
    var_type_t type = VAR_ENV;
    char variable[len];

    for (int i = 0; i <= len; i++)
        variable[i] = 0;
    strncpy(variable, LINE + off, len);
    if (exist_in_shell_var(context, off - 1 - curly, curly, variable))
        return true;
    TAILQ_FOREACH(var, VARQ, entries) {
        if (strncmp(var->name, variable, len) == 0) {
            LINE = sub_variable(len + curly, var->name + len + 1,
                                off - 1 - curly, LINE);
            return true;
        }
    }
    if (fprintf(stderr, "%s: Undefined variable.\n", variable) < 0)
        DIE;
    return false;
}

static bool handle_variable(mysh_t *context, int off)
{
    int len = 0;
    int curly = 0;

    if (LINE[off + 1] == '{') {
        off += 1;
        curly = 1;
    }
    for (; IS_ALPHANUM(LINE[off + len + 1]); len++);
    return variable_exist(context, off + 1, len, curly);
}

bool substitute_variables(mysh_t *context)
{
    if (handle_curly_brackets(context) == false)
        return false;
    for (int i = 0; LINE[i] != '\0'; i++) {
        if (LINE[i] != '$')
            continue;
        P = LINE + i + 1;
        if (IS_SEPARATOR || *P == '\n')
            continue;
        if (handle_variable(context, i) == false) {
            STATUS = 1;
            return false;
        }
    }
    return true;
}
