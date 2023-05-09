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
#include "mysh/commands.h"

static bool init(mysh_t *context, char **env)
{
    TAILQ_INIT(ENVQ);
    TAILQ_INIT(&context->pipelines);
    load_env(context, env);
    return false;
}

void cleanup(mysh_t *context)
{
    destroy_env(context);
    free_pipelines(context);
    free(LINE);
}

void mysh(mysh_t *context, char **env)
{
    if (init(context, env))
        exit(84);
    prompt(context), errno = 0;
    for (; !EXIT && GET_LINE != -1; LINE_ITERATION) {
        LINE = input_edition(context);
        if (LEN > 1 && *LINE != '#' && !parse_command_line(context))
            TAILQ_FOREACH(PIPELINE, &context->pipelines, entries)
                run_pipeline(context);
    }
    if (errno)
        DIE;
    TTY_WRITE("exit\n", 5);
    cleanup(context);
}
