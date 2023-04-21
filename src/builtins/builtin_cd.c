/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_cd.c
*/

#include <unistd.h>
#include <malloc.h>
#include <sys/stat.h>

#include "mysh/env.h"
#include "ice/array.h"
#include "ice/string.h"
#include "ice/printf.h"
#include "mysh/miscellaneous.h"

static bool verif_pwd(char *pwd, char *path, mysh_t *context)
{
    struct stat st;

    if (!pwd)
        return true;
    if (stat((pwd + 4), &st) == -1) {
        display_error(context, "%s: No such file or directory.\n", path);
        return true;
    }
    if (!S_ISDIR(st.st_mode)) {
        display_error(context, "%s: Not a directory.\n", path);
        return true;
    }
    return false;
}

static env_t *update_pwd(char *src, char *path, mysh_t *context)
{
    char *pwd;

    ice_asprintf(&pwd, "PWD=%s/%s", src, path);
    if (verif_pwd(pwd, path, context))
        return ENV;
    if (chdir(pwd +4))
        return ENV;
    ENV->env = set_env(context, "OLDPWD", get_env(context, "PWD"));
    ENV->env = set_env(context, "PWD", pwd + 4);
    free(pwd);
    if (!ENV->env)
        return ENV;
    return ENV;
}

static env_t *update_pwd_home(mysh_t *context)
{
    char *home = get_env(context, "HOME");

    if (!home) {
        display_error(context, "No $home set.\n", NULL);
        return ENV;
    }
    return update_pwd(home, "", context);
}

static env_t *update_pwd_oldpwd(mysh_t *context)
{
    char *oldpwd = get_env(context, "OLDPWD");

    if (!oldpwd) {
        display_error(context, "cd: No such file or directory.\n", NULL);
        return ENV;
    }
    return update_pwd(oldpwd, "", context);
}

env_t *builtin_cd(char **av, mysh_t *context)
{
    if (ice_array_len((void **)av) > 2) {
        display_error(context, "cd: Too many arguments.\n", NULL);
        return ENV;
    }
    if (!av[1] || !ice_strcmp(av[1], "~"))
        return update_pwd_home(context);
    if (av[1][0] == '/')
        return update_pwd("", av[1], context);
    if (ice_strcmp(av[1], "-") == 0)
        return update_pwd_oldpwd(context);
    return update_pwd(get_env(context, "PWD"), av[1], context);
}
