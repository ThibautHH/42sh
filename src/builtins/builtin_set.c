/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_set.c
*/

#include <stdio.h>

#include "mysh.h"

static void write_error(mysh_t *context, char *error)
{
    if (fputs(error, stderr) < 0)
        DIE;
    STATUS = 1;
}

static bool check_name(mysh_t *context, char *name)
{
    for (; *name && *name != '='; name++)
        if (!IS_ALPHANUM(*name)) {
            write_error(context, "set: Variable name must contain"
                " alphanumeric characters.\n");
            return true;
        }
    return false;
}

void builtin_set(mysh_t *context)
{
    if (CMDARGC < 2)
        return builtin_at(context);
    for (size_t i = 1, nlen; i < CMDARGC; i++) {
        if (!IS_ALPHA(*(CMDARGS[i]))) {
            write_error(context, "set: Variable name must"
                " begin with a letter.\n");
            return;
        }
        nlen = ice_strtil(CMDARGS[i], '=');
        if (check_name(context, CMDARGS[i]))
            return;
        if (CMDARGS[i][nlen]) {
            CMDARGS[i][nlen] = '\0';
            var_update(context, CMDARGS[i], CMDARGS[i] + nlen + 1, VAR_SHELL);
        } else
            var_update(context, CMDARGS[i], "", VAR_SHELL);
    }
    STATUS = 0;
}
