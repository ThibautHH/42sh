/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** mysh.c
*/

#include <sys/auxv.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "mysh.h"

static _Bool is_shebang_invoked(char *arg, char *av0)
{
    FILE *file; char *line = NULL;
    size_t size = 0, av0_len = strlen(av0);
    ssize_t readln; _Bool ret;

    if (access(arg, F_OK) == -1 || access(arg, X_OK) == -1)
        return 0;
    file = fopen(arg, "r");
    if (!file)
        perror(arg), exit(84);
    errno = 0;
    if ((readln = getline(&line, &size, file)) == -1) {
        if (errno) exit(84);
        else
            return 0;
    }
    fclose(file);
    ret = !(strncmp(line, "#!", 2) || strncmp(line + 2, av0, av0_len))
        && IS_WHITESPACE(line[2 + av0_len]);
    free(line);
    return ret;
}

static void handle_shebang_invocation(char **argv)
{
    char *prog_path = (char *)getauxval(AT_EXECFN);

    if (!prog_path)
        perror("getauxval"), exit(84);
    if (!strcmp(prog_path, *argv))
        return;
    for (char **av = argv; *(++av);)
        if (!strcmp(prog_path, *av) && is_shebang_invoked(*av, *argv)
            && (freopen(prog_path, "r", stdin) == NULL))
                perror(prog_path), exit(84);
}

int main(UNUSED int ac, char **av, char **env)
{
    mysh_t context = {0};
    handle_shebang_invocation(av);
    mysh(&context, env);
    return context.status;
}
