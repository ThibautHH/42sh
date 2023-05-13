/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_cmd_path.c
*/

#include <malloc.h>
#include <unistd.h>

#include "mysh/commands.h"

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

static char *set_bin_to_path(mysh_t *context, char **binpath, char **p,
    path_size_t *pathsize)
{
    bool slash;
    char *tmp;

    slash = ((*binpath)[pathsize->dirlen - 1] == '/');
    if (!slash)
        (*binpath)[pathsize->dirlen++] = '/';
    ice_strcpy(*binpath + pathsize->dirlen, CMDCMD);
    (*binpath)[pathsize->pathsize - slash - 1] = '\0';
    if (!access(*binpath, F_OK)) {
        tmp = *binpath;
        *binpath = NULL;
        return tmp;
    }
    *p += pathsize->dirlen - !slash + 1;
    return NULL;
}

static char *compose_path(mysh_t *context, char **p)
{
    static char *binpath = NULL;
    path_size_t pathsize;

    if (!p) {
        free(binpath);
        binpath = NULL;
        return NULL;
    }
    pathsize.dirlen = ice_strtil(*p, ':');
    if (!pathsize.dirlen)
        return NULL;
    pathsize.pathsize = pathsize.dirlen + ice_strlen(CMDCMD) + 2;
    binpath = realloc(binpath, pathsize.pathsize);
    if (!binpath)
        DIE;
    ice_strncpy2(binpath, *p, pathsize.dirlen);
    return set_bin_to_path(context, &binpath, p, &pathsize);
}

static char *get_bin_path(mysh_t *context)
{
    char *path = GET_VAR("PATH", ENV);
    char *binpath = NULL;
    size_t confstrlen = confstr(_CS_PATH, NULL, 0);

    if (!path) {
        if (!confstrlen)
            return NULL;
        path = malloc(confstrlen * sizeof(char));
        if (!path)
            DIE;
        confstr(_CS_PATH, path, confstrlen);
    }
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
