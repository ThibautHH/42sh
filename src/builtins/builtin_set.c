/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_set.c
*/

#include <stdio.h>
#include <string.h>

#include "mysh.h"

static void write_error(mysh_t *context, char *error)
{
    if (fputs(error, stderr) < 0)
        DIE;
    STATUS = 1;
}

static void local_var_update(mysh_t *context, char *name, char *value)
{
    var_t *var;
    var_type_t type = VAR_SHELL;

    TAILQ_FOREACH(var, VARQ, entries)
        if (is_var_named(var, name)) {
            value == NULL ? *VARV(var) = 0 : ice_strcpy(VARV(var), value);
            return;
        }
    var = malloc(sizeof(var_t));
    if (!var)
        DIE;
    var->name = &(*VARV(var)) - (ice_strlen(name) + 1);
    ice_strcpy(VARN(var), name);
    if (value != NULL)
        ice_strcpy(VARV(var), value);
    VARV(var)[-1] = '=';
    TAILQ_INSERT_TAIL(VARQ, var, entries);
    VARC++;
    free(name);
}

static void display_local_var(mysh_t *context)
{
    var_t *var;
    var_type_t type = VAR_SHELL;
    int len = 0;

    TAILQ_FOREACH(var, VARQ, entries) {
        for (; var->name[len] != '='; len++);
        if (printf("%.*s", len, var->name) < 0)
            DIE;
        if (var->name[len + 1] != 0 && printf("\t") < 0)
            DIE;
        if (var->name[len + 1] == 0 && printf("\n") < 0)
            DIE;
        if (var->name[len + 1] == 0)
            continue;
        if (printf("%s\n", var->name + len + 1) < 0)
            DIE;
    }
    STATUS = 0;
}

size_t get_name_len(mysh_t *context, size_t i)
{
    size_t name_len = 1;

    for (size_t y = 0; CMDARGS[i][y]; y++) {
        if (!IS_ALPHANUM(CMDARGS[i][y]) && (CMDARGS[i][y] != '='
            || CMDARGS[i][y + 1] == 0 || y == 0)) {
            write_error(context, "set: Variable name must contain"
                " alphanumeric characters.\n");
            return 0;
        }
        if (CMDARGS[i][y] == '=') {
            return name_len;
        }
        name_len++;
    }
    return name_len;
}

void builtin_set(mysh_t *context)
{
    size_t name_len;
    char *value;
    char *name;

    if (CMDARGC < 2)
        return display_local_var(context);
    for (size_t i = 1; i < CMDARGC; i++) {
        value = NULL;
        name_len = get_name_len(context, i);
        if (name_len == 0)
            return;
        value = CMDARGS[i] + name_len;
        name = malloc(sizeof(char) * name_len);
        name[name_len - 1] = 0;
        strncpy(name, CMDARGS[i], name_len - 1);
        local_var_update(context, name, value);
    }
    STATUS = 0;
}
