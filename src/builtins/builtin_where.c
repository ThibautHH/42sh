/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** builtin_where.c
*/

#include <stdio.h>
#include <string.h>

#include "mysh.h"
#include "ice/array.h"
#include "ice/printf.h"

static bool is_builtin(mysh_t *context, char *arg)
{
    for (size_t j = 0; j < BUILTIN_COUNT; j++) {
        if (!strcmp(arg, BUILTINS[j].name)) {
            DWRITE(STDOUT_FILENO, arg, strlen(arg));
            DWRITE(STDOUT_FILENO, " is a shell built-in\n", 21);
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
        if (ice_asprintf(&binary, "%s/%s", path[i], arg) < 0)
            DIE;
        if (!access(binary, F_OK)) {
            DWRITE(STDOUT_FILENO, binary, strlen(binary));
            DWRITE(STDOUT_FILENO, "\n", 1);
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
        DWRITE(STDERR_FILENO, "where: Too few arguments.\n", 26);
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
