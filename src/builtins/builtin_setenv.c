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
            DWRITE(STDERR_FILENO, "setenv: Variable name must contain "
                "alphanumeric characters.\n", 60);
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
        DWRITE(STDERR_FILENO, "setenv: Too many arguments.\n", 28);
        STATUS = 1;
        return;
    }
    exec_setenv(context);
}
