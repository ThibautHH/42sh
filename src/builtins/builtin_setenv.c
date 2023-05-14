/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_setenv.c
*/

#include "mysh.h"

static void exec_setenv(mysh_t *context)
{
    char *name = CMDARGS[1];
    char *value;

    for (size_t i = 0; name[i]; i++)
        if (!(IS_ALPHANUM(name[i]) || name[i] == '_')) {
            ERRPRINT("setenv: Variable name must contain alphanumeric "
                "characters.\n");
            STATUS = 1;
            return;
        }
    value = (CMDARGC == 3) ? CMDARGS[2] : "";
    var_update(context, name, value, VAR_ENV);
    STATUS = 0;
}

void builtin_setenv(mysh_t *context)
{
    if (CMDARGC < 2)
        return builtin_env(context);
    if (CMDARGC > 3) {
        ERRPRINT("setenv: Too many arguments.\n");
        STATUS = 1;
        return;
    }
    exec_setenv(context);
}
