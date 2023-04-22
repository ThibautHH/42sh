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
#include "ice/array.h"
#include "ice/string.h"
#include "ice/printf.h"
#include "mysh/miscellaneous.h"

static uc_t handle_cd_errors(mysh_t *context, char *path)
{
    switch (errno) {
    case EACCES:
        if (ice_dprintf(STDERR_FILENO, "%s: Permission denied.\n", path) < 0)
            DIE;
        break;
    case ENOENT:
        if (ice_dprintf(STDERR_FILENO, "%s: No such file "
            "or directory.\n", path) < 0)
            DIE;
        break;
    case ENOTDIR:
        if (ice_dprintf(STDERR_FILENO, "%s: Not a directory.\n", path) < 0)
            DIE;
        break;
    default: DIE;
    }
    return 1;
}

bool builtin_cd(char **av, mysh_t *context)
{
    size_t argc = ice_array_len((void **)av);
    if (argc > 2) {
        DWRITE(STDERR_FILENO, "cd: Too many arguments.\n", 24);
        return (STATUS = 1);
    }
    char *prev_pwd = ice_strdup(GET_ENV("PWD"));
    char *path = argc == 2
        ? (ice_strcmp(av[1], "-")
            ? av[1] : GET_ENV("OLDPWD"))
        : GET_ENV("HOME");
    if (chdir(path ? path : "") == -1)
        return (STATUS = handle_cd_errors(context, path));
    getcwd(GET_ENV("PWD"), 4096);
    env_update(context, "OLDPWD", prev_pwd);
    free(prev_pwd);
    return (STATUS = 0);
}
