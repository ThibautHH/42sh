/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_setenv.c
*/

#include "mysh.h"
#include "mysh/builtins.h"
#include "mysh/parsing.h"

void builtin_set(mysh_t *context)
{
    if (CMDARGC < 2)
        return builtin_at(context);
    if (CMDARGC > 3) {
        DWRITE(STDERR_FILENO, "setenv: Too many arguments.\n", 28);
        STATUS = 1;
        return;
    }
    char *name = CMDARGS[1];
    for (size_t i = 0; name[i]; i++)
        if (!(IS_ALPHANUM(name[i]) || name[i] == '_')) {
            DWRITE(STDERR_FILENO, "setenv: Variable name must contain "
                "alphanumeric characters.\n", 60);
            STATUS = 1;
            return;
        }
    char *value = CMDARGC == 3 ? CMDARGS[2] : "";
    var_update(context, name, value, VAR_SHELL);
    STATUS = 0;
}
