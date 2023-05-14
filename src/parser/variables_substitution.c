/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** substitute_variables
*/

#include <stdio.h>
#include <string.h>

#include "mysh/parsing_functions.h"

static void sub_variable(int var_len, char *value, int off, mysh_t *context)
{
    int len = LEN - (var_len + 1) + strlen(value);
    char *newline = malloc(sizeof(char) * (len + 1));

    if (!newline)
        DIE;
    for (int i = 0; i <= len; i++)
        newline[i] = 0;
    strncpy(newline, LINE, off);
    LINE += off + var_len + 1;
    if (*LINE == '}') {
        LINE++;
        off++;
    }
    strcat(newline, value);
    strcat(newline, LINE);
    LINE -= off + var_len + 1;
    LINE = realloc(LINE, len + 1);
    LEN = len;
    ice_strcpy(LINE, newline);
    free(newline);
}

static bool exist_in_shell_var(mysh_t *context, int off, int curly,
    char *variable)
{
    var_t *var;
    var_type_t type = VAR_SHELL;
    int len = strlen(variable);

    TAILQ_FOREACH(var, VARQ, entries) {
        if (strncmp(var->name, variable, len) == 0) {
            sub_variable(len + curly, VARV(var), off, context);
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
            sub_variable(len + curly, VARV(var), off - 1 - curly, context);
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
    for (; IS_ALPHANUM(LINE[off + len + 1])
        || LINE[off + len + 1] == '_'; len++);
    return variable_exist(context, off + 1, len, curly);
}

bool substitute_variables(mysh_t *context)
{
    if (!handle_curly_brackets(context))
        return false;
    for (int i = 0; LINE[i] != '\0'; i++) {
        if (LINE[i] != '$')
            continue;
        P = LINE + i + 1;
        if (IS_SEPARATOR || *P == '\n')
            continue;
        if (!handle_variable(context, i)) {
            STATUS = 1;
            return false;
        }
    }
    return true;
}
