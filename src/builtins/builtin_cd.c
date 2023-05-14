/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_cd.c
*/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "mysh.h"

static void handle_cd_errors(mysh_t *context, char *path)
{
    switch (errno) {
        case EACCES:
            ERRPRINT("%s: Permission denied.\n", path);
            break;
        case ENOENT:
            ERRPRINT("%s: No such file or directory.\n", path);
            break;
        case ENOTDIR:
            ERRPRINT("%s: Not a directory.\n", path);
            break;
        default: DIE;
    }
}

static void exec_cd(mysh_t *context)
{
    char *prev_pwd;
    char *path;

    prev_pwd = ice_strdup(GET_VAR("PWD", ENV));
    if (CMDARGC == 2)
        path = ice_strcmp(CMDARGS[1], "-") ? CMDARGS[1] :
            GET_VAR("OLDPWD", ENV);
    else
        path = GET_VAR("HOME", ENV);
    path = (path) ? path : "";
    if (chdir(path) == -1) {
        STATUS = 1;
        free(prev_pwd);
        handle_cd_errors(context, path);
        return;
    }
    getcwd(GET_VAR("PWD", ENV), VARVLEN);
    var_update(context, "OLDPWD", prev_pwd, VAR_ENV);
    free(prev_pwd);
    STATUS = 0;
}

void builtin_cd(mysh_t *context)
{
    if (CMDARGC > 2) {
        ERRPRINT("cd: Too many arguments.\n");
        STATUS = 1;
        return;
    }
    exec_cd(context);
}
