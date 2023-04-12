/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtins_cd.c
*/

#include <unistd.h>
#include <malloc.h>
#include <sys/stat.h>

#include "mysh/env.h"
#include "ice/array.h"
#include "ice/string.h"
#include "ice/printf.h"
#include "mysh/miscellaneous.h"

static bool verif_pwd(char *pwd, char *path, env_t *env)
{
    struct stat st;

    if (!pwd)
        return true;
    if (stat((pwd + 4), &st) == -1) {
        display_error(env, "%s: No such file or directory.\n", path);
        return true;
    }
    if (!S_ISDIR(st.st_mode)) {
        display_error(env, "%s: Not a directory.\n", path);
        return true;
    }
    return false;
}

static env_t *update_pwd(char *src, char *path, env_t *env)
{
    char *pwd;

    ice_asprintf(&pwd, "PWD=%s/%s", src, path);
    if (verif_pwd(pwd, path, env))
        return env;
    if (chdir(pwd +4))
        return env;
    env->env = set_env(env, "OLDPWD", get_env(env, "PWD"));
    env->env = set_env(env, "PWD", pwd + 4);
    free(pwd);
    if (!env->env)
        return env;
    return env;
}

static env_t *update_pwd_home(env_t *env)
{
    char *home = get_env(env, "HOME");

    if (!home) {
        display_error(env, "No $home set.\n", NULL);
        return env;
    }
    return update_pwd(home, "", env);
}

static env_t *update_pwd_oldpwd(env_t *env)
{
    char *oldpwd = get_env(env, "OLDPWD");

    if (!oldpwd) {
        display_error(env, "cd: No such file or directory.\n", NULL);
        return env;
    }
    return update_pwd(oldpwd, "", env);
}

env_t *builtin_cd(char **av, env_t *env)
{
    if (ice_array_len((void **)av) > 2) {
        display_error(env, "cd: Too many arguments.\n", NULL);
        return env;
    }
    if (!av[1] || !ice_strcmp(av[1], "~"))
        return update_pwd_home(env);
    if (av[1][0] == '/')
        return update_pwd("", av[1], env);
    if (ice_strcmp(av[1], "-") == 0)
        return update_pwd_oldpwd(env);
    return update_pwd(get_env(env,"PWD"), av[1], env);
}
