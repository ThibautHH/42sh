/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** builtin_which.c
*/

#include <string.h>

#include "mysh.h"
#include "ice/array.h"

static bool is_builtin(mysh_t *context, char *arg)
{
    for (size_t j = 0; j < BUILTIN_COUNT; j++) {
        if (!strcmp(arg, BUILTINS[j].name)) {
            PRINT("%s: shell built-in command.\n", arg);
            return true;
        }
    }
    return false;
}

static bool is_binary(mysh_t *context, char *arg)
{
    char *binary;
    char **path = ice_strsplit(GET_VAR("PATH", ENV), ":");

    for (ull_t i = 0; path[i]; i++) {
        if (asprintf(&binary, "%s/%s", path[i], arg) < 0)
            DIE;
        if (!access(binary, F_OK)) {
            PRINT("%s\n", binary);
            free(binary);
            return true;
        }
        free(binary);
    }
    ice_free_array((void **)path);
    return false;
}

void builtin_which(mysh_t *context)
{
    bool found = false;

    if (CMDARGC < 2) {
        ERRPRINT("which: Too few arguments.\n");
        STATUS = 1;
        return;
    }
    STATUS = 0;
    for (size_t i = 1; i < CMDARGC; i++) {
        found = is_builtin(context, CMDARGS[i]);
        if (!found)
            found = is_binary(context, CMDARGS[i]);
        if (!found) {
            PRINT("%s: Command not found.\n", CMDARGS[1]);
            STATUS = 1;
        }
        found = false;
    }
}
