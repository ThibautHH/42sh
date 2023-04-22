/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** mysh.c
*/


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mysh.h"
#include "mysh/parser.h"

static bool init(mysh_t *context, char **env)
{
    TAILQ_INIT(ENVQ);
    load_env(context, env);
    return false;
}

static void cleanup(mysh_t *context)
{
    destroy_env(context);
    free(LINE);
}

void die(mysh_t *context, uc_t status)
{
    cleanup(context);
    exit(status);
}

void mysh(mysh_t *context, char **env)
{
    size_t size = 0;

    if (init(context, env))
        exit(84);
    prompt(context), errno = 0;
    for (ssize_t len; GET_LINE != -1; prompt(context), errno = 0) {
        if (len == 1)
            continue;
        LINE[len - 1] = '\0';
        if (handle_sequence(LINE, context))
            DIE;
    }
    if (errno)
        DIE;
    TTY_WRITE("exit\n", 5);
    cleanup(context);
}
