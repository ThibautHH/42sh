/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_cmd_path.c
*/

#include <malloc.h>
#include <unistd.h>

#include "mysh.h"

static bool set_cmd_path(mysh_t *context, char *path)
{
    if (access(path, X_OK)) {
        if (fprintf(stderr, "%s: Permission denied.\n", path) < 0)
            DIE;
        STATUS = 1;
        return true;
    }
    CMDPATH = path;
    return false;
}

static char *compose_path(mysh_t *context, char **p)
{
    static char *binpath = NULL;
    size_t pathsize;
    size_t dirlen;
    bool slash;
    char *tmp;

    if (!p) {
        free(binpath);
        binpath = NULL;
        return NULL;
    }
    dirlen = ice_strtil(*p, ':');
    if (!dirlen)
        return NULL;
    pathsize = dirlen + ice_strlen(CMDCMD) + 2;
    binpath = realloc(binpath, pathsize);
    if (!binpath)
        DIE;
    ice_strncpy2(binpath, *p, dirlen);
    slash = (binpath[dirlen - 1] == '/');
    if (!slash)
        binpath[dirlen++] = '/';
    ice_strcpy(binpath + dirlen, CMDCMD);
    binpath[pathsize - slash - 1] = '\0';
    if (!access(binpath, F_OK)) {
        tmp = binpath;
        binpath = NULL;
        return tmp;
    }
    *p += dirlen - !slash + 1;
    return NULL;
}

static char *get_bin_path(mysh_t *context)
{
    char *path = GET_VAR("PATH", ENV);
    char *binpath = NULL;

    if (!path)
        return NULL;
    for (char *p = path; p == path || p[-1] == ':';) {
        binpath = compose_path(context, &p);
        if (binpath)
            return binpath;
    }
    return compose_path(context, NULL);
}

bool get_cmd_path(mysh_t *context)
{
    char *binary;

    for (size_t i = 0; i < BUILTIN_COUNT; i++)
        if (!ice_strcmp(CMDCMD, BUILTINS[i].name)) {
            CMD->is_builtin = true;
            CMDCOMMAND.id = BUILTINS[i].id;
            return false;
        }
    if (!CMDCMD[ice_strtil(CMDCMD, '/')]) {
        binary = get_bin_path(context);
        if (binary)
            return set_cmd_path(context, binary);
    } else if (!access(CMDCMD, F_OK))
        return set_cmd_path(context, ice_strdup(CMDCMD));
    if (fprintf(stderr, "%s: Command not found.\n", CMDCMD) < 0)
        DIE;
    STATUS = 1;
    return true;
}
