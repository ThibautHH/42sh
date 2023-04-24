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

static void set_cmd_path(mysh_t *context, char *path)
{
    if (access(path, X_OK)) {
        ice_dprintf(STDERR_FILENO, "%s: Permission denied.\n", path);
        die(context, 1);
    }
    CMDPATH = path;
}

static char *compose_path(mysh_t *context, char **p)
{
    size_t dirlen = ice_strtil(*p, ':');
    if (!dirlen)
        return NULL;
    static char *binpath = NULL;
    static size_t old_pathsize = 0;
    size_t pathsize = dirlen + ice_strlen(CMDCMD) + 2;
    binpath = ice_realloc2(binpath, old_pathsize, pathsize);
    if (!binpath) DIE;
    old_pathsize = pathsize;
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
    char *path = GET_ENV("PATH"), *binpath = NULL;
    for (char *p = path; *p && (p == path || p[-1] == ':');)
        if ((binpath = compose_path(context, &p)))
            return binpath;
    return NULL;
}

void get_cmd_path(mysh_t *context)
{
    for (size_t i = 0; i < BUILTIN_COUNT; i++)
        if (!ice_strcmp(CMDCMD, BUILTINS[i].name)) {
            CMD->is_builtin = true;
            CMDCOMMAND.id = BUILTINS[i].id;
            return;
        }
    if (!CMDCMD[ice_strtil(CMDCMD, '/')]) {
        char *binary = get_bin_path(context);
        if (binary)
            return set_cmd_path(context, binary);
    } else if (!access(CMDCMD, F_OK))
        return set_cmd_path(context, ice_strdup(CMDCMD));
    ice_dprintf(STDERR_FILENO, "%s: Command not found.\n", CMDCMD);
    die(context, 1);
}
