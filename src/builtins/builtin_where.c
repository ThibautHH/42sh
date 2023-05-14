/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** builtin_where.c
*/

#include <string.h>

#include "mysh.h"
#include "ice/array.h"

static bool is_builtin(mysh_t *context, char *arg)
{
    for (size_t j = 0; j < BUILTIN_COUNT; j++) {
        if (!strcmp(arg, BUILTINS[j].name)) {
            PRINT("%s is a shell built-in\n", arg);
            return true;
        }
    }
    return false;
}

static bool is_binary(mysh_t *context, char *arg)
{
    char *binary;
    char **path = ice_strsplit(GET_VAR("PATH", ENV), ":");
    bool found = false;

    for (ull_t i = 0; path[i]; i++) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
        if (asprintf(&binary, "%s/%s", path[i], arg) < 0)
#pragma GCC diagnostic pop
            DIE;
        if (!access(binary, F_OK)) {
            PRINT("%s\n", binary);
            found = true;
        }
        free(binary);
    }
    ice_free_array((void **)path);
    return found;
}

void builtin_where(mysh_t *context)
{
    bool found = false;

    if (CMDARGC < 2) {
        ERRPRINT("where: Too few arguments.\n");
        STATUS = 1;
        return;
    }
    STATUS = 0;
    for (size_t i = 1; i < CMDARGC; i++) {
        found = is_builtin(context, CMDARGS[i]);
        found = is_binary(context, CMDARGS[i]) || (found);
        if (!found)
            STATUS = 1;
        found = false;
    }
}
