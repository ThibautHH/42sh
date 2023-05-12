/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_cd.c
*/

#include <errno.h>
#include <malloc.h>
#include <unistd.h>

#include "mysh.h"
#include "ice/printf.h"

static void handle_cd_errors(mysh_t *context, char *path)
{
    switch (errno) {
        case EACCES:
            if (ice_dprintf(STDERR_FILENO, "%s: Permission denied.\n",
                path) < 0)
                DIE;
            break;
        case ENOENT:
            if (ice_dprintf(STDERR_FILENO, "%s: No such file "
                "or directory.\n", path) < 0)
                DIE;
            break;
        case ENOTDIR:
            if (ice_dprintf(STDERR_FILENO, "%s: Not a directory.\n",
                path) < 0)
                DIE;
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
        DWRITE(STDERR_FILENO, "cd: Too many arguments.\n", 24);
        STATUS = 1;
        return;
    }
    exec_cd(context);
}
