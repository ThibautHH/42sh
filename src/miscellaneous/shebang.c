/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** shebang.c
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/auxv.h>

#include "mysh.h"

static FILE *get_shebang_file(char *arg)
{
    FILE *file = fopen(arg, "r");

    if (!file) {
        perror(arg);
        exit(84);
    }
    return file;
}

static bool get_shebang_line(FILE *file, char **line)
{
    size_t size = 0;
    ssize_t readln;

    errno = 0;
    readln = getline(line, &size, file);
    if (readln == -1) {
        if (errno)
            exit(84);
        else
            return false;
    }
    return true;
}

static bool is_shebang_invoked(char *arg, char *av0)
{
    size_t av0_len = strlen(av0);
    char *line = NULL;
    FILE *file;
    bool ret;

    if (access(arg, F_OK) == -1 || access(arg, X_OK) == -1)
        return false;
    file = get_shebang_file(arg);
    if (!get_shebang_line(file, &line))
        return false;
    if (fclose(file) == EOF) {
        perror(arg);
        exit(84);
    }
    ret = !(strncmp(line, "#!", 2) != 0
        || strncmp(line + 2, av0, av0_len) != 0)
        && IS_WHITESPACE(line[2 + av0_len]);
    free(line);
    return ret;
}

void handle_shebang_invocation(char **argv)
{
    char *prog_path = (char *)getauxval(AT_EXECFN);

    if (!prog_path) {
        perror("getauxval");
        exit(84);
    }
    if (!strcmp(prog_path, *argv))
        return;
    for (char **av = argv; *(++av);)
        if (!strcmp(prog_path, *av) && is_shebang_invoked(*av, *argv)
            && (!freopen(prog_path, "r", stdin))) {
            perror(prog_path);
            exit(84);
        }
}
