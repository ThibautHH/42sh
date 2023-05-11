/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_setenv.c
*/

#include <stdio.h>

#include "mysh.h"

static void write_error(mysh_t *context, char *error)
{
    if (fputs(error, stderr) < 0)
        DIE;
    STATUS = 1;
}

static void exec_set(mysh_t *context)
{
    char *name = CMDARGS[1];
    char *value;

    for (size_t i = 0; name[i]; i++)
        if (!(IS_ALPHANUM(name[i]) || name[i] == '_')) {
            write_error(context, "set: Variable name must contain "
                "alphanumeric characters.\n");
            return;
        }
    value = (CMDARGC == 3) ? CMDARGS[2] : "";
    var_update(context, name, value, VAR_SHELL);
    STATUS = 0;
}

void builtin_set(mysh_t *context)
{

    if (CMDARGC < 2)
        return builtin_at(context);
    if (CMDARGC > 3) {
        write_error(context, "set: Too many arguments.\n");
        return;
    }
    exec_set(context);
}
