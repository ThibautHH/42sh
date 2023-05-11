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
#include "mysh/alias.h"
#include "mysh/commands.h"

static bool init(mysh_t *context, char **env)
{
    for (var_type_t type = VAR_ENV; type <= VAR_SHELL; type++)
        TAILQ_INIT(VARQ);
    TAILQ_INIT(&context->pipelines);
    load_env(context, env);
    TAILQ_INIT(ALIASQ);
    return false;
}

void cleanup(mysh_t *context)
{
    for (var_type_t type = VAR_ENV; type <= VAR_SHELL; type++)
        destroy_vars(context, type);
    free_pipelines(context);
    destroy_alias(context);
    free(LINE);
}

void mysh(mysh_t *context, char **env)
{
    if (init(context, env))
        exit(84);
    prompt(context), errno = 0;
    for (; !EXIT && GET_LINE != -1; LINE_ITERATION)
        if (LEN > 1 && *LINE != '#' && substitute_alias(context)
            && !parse_command_line(context))
            TAILQ_FOREACH(PIPELINE, &context->pipelines, entries)
                run_pipeline(context);
    if (errno)
        DIE;
    TTY_WRITE("exit\n", 5);
    cleanup(context);
}
