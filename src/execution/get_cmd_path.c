/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_cmd_path.c
*/

#include <malloc.h>
#include <unistd.h>

#include "ice/array.h"
#include "ice/memory.h"
#include "ice/string.h"
#include "ice/printf.h"

#include "mysh.h"
#include "mysh/builtins.h"
#include "mysh/parsing.h"

static _Bool set_cmd_path(mysh_t *context, char *path)
{
    if (access(path, X_OK)) {
        ice_dprintf(STDERR_FILENO, "%s: Permission denied.\n", path);
        return (STATUS = 1);
    }
    CMDPATH = path;
    return 0;
}

static char *compose_path(mysh_t *context, char **p)
{
    static char *binpath = NULL;
    if (!p && (free(binpath), 1))
        return (binpath = NULL);
    size_t dirlen = ice_strtil(*p, ':');
    if (!dirlen)
        return NULL;
    size_t pathsize = dirlen + ice_strlen(CMDCMD) + 2;
    binpath = realloc(binpath, pathsize);
    if (!binpath) DIE;
    ice_strncpy2(binpath, *p, dirlen);
    _Bool slash = binpath[dirlen - 1] == '/';
    if (!slash)
        binpath[dirlen++] = '/';
    ice_strcpy(binpath + dirlen, CMDCMD);
    binpath[pathsize - slash - 1] = '\0';
    if (!access(binpath, F_OK)) {
        char *tmp = binpath; binpath = NULL;
        return tmp;
    } *p += dirlen - !slash + 1;
    return NULL;
}

static char *get_bin_path(mysh_t *context)
{
    char *path = GET_VAR("PATH", ENV), *binpath = NULL;
    if (!path)
        return NULL;
    for (char *p = path; p[-1] && (p == path || p[-1] == ':');)
        if ((binpath = compose_path(context, &p)))
            return binpath;
    return compose_path(context, NULL);
}

_Bool get_cmd_path(mysh_t *context)
{
    for (size_t i = 0; i < BUILTIN_COUNT; i++)
        if (!ice_strcmp(CMDCMD, BUILTINS[i].name)) {
            CMD->is_builtin = true;
            CMDCOMMAND.id = BUILTINS[i].id;
            return 0;
        }
    if (!CMDCMD[ice_strtil(CMDCMD, '/')]) {
        char *binary = get_bin_path(context);
        if (binary)
            return set_cmd_path(context, binary);
    } else if (!access(CMDCMD, F_OK))
        return set_cmd_path(context, ice_strdup(CMDCMD));
    ice_dprintf(STDERR_FILENO, "%s: Command not found.\n", CMDCMD);
    return (STATUS = 1);
}
