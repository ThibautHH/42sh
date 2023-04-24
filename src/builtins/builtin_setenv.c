/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_setenv.c
*/

#include "mysh.h"
#include "ice/array.h"
#include "mysh/miscellaneous.h"
#include "mysh/builtins.h"
#include "mysh/parsing.h"

bool builtin_setenv(mysh_t *context)
{
    if (CMDARGC < 2)
        return builtin_env(context);
    if (CMDARGC > 3) {
        DWRITE(STDERR_FILENO, "setenv: Too many arguments.\n", 28);
        return (STATUS = 1);
    }
    char *name = CMDARGS[1];
    for (size_t i = 0; name[i]; i++)
        if (!(IS_ALPHANUM(name[i]) || name[i] == '_')) {
            DWRITE(STDERR_FILENO, "setenv: Variable name must contain "
                "alphanumeric characters.\n", 60);
            return (STATUS = 1);
        }
    char *value = CMDARGC == 3 ? CMDARGS[2] : "";
    env_update(context, name, value);
    return (STATUS = 0);
}
