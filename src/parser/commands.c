/*
** EPITECH PROJECT, 2023
** Minishell 2
** File description:
** Command structure management
*/

#include <malloc.h>

#include "mysh.h"

static void free_command(mysh_t *context)
{
    TAILQ_REMOVE(&PIPELINE->commands, CMD, entries);
    for (size_t i = 0; i < CMDARGC; i++)
        free(CMDARGS[i]);
    for (uc_t i = 0; i < 3; i++)
        if (CMDRED(i).type)
            free((CMDRED(i).type == REDIR_FILE)
                ? CMDREDFILE(i).name : CMDRED(i).target.string);
    free(CMDARGS);
    if (!(CMD->is_builtin))
        free(CMDPATH);
    free(CMD);
}

void free_pipelines(mysh_t *context)
{
    pipeline_t *ppl_tmp;

    TAILQ_FOREACH_SAFE(PIPELINE, &context->pipelines, entries, ppl_tmp) {
        command_t *cmd_tmp;
        TAILQ_REMOVE(&context->pipelines, PIPELINE, entries);
        TAILQ_FOREACH_SAFE(CMD, &PIPELINE->commands, entries, cmd_tmp)
            free_command(context);
        free(PIPELINE);
    }
}

void new_pipeline(mysh_t *context, sequence_mode_t mode)
{
    pipeline_t *ppl = malloc(sizeof(pipeline_t));

    if (!ppl)
        DIE;
    ppl->mode = mode;
    TAILQ_INIT(&ppl->commands);
    TAILQ_INSERT_TAIL(&context->pipelines, ppl, entries);
    PIPELINE = ppl;
}

void new_command(mysh_t *context)
{
    command_t *cmd = calloc(1, sizeof(command_t));

    if (!cmd)
        DIE;
    for (uc_t i = 0; i < 3; i++)
        cmd->redirections[i].type = REDIR_NONE;
    TAILQ_INSERT_TAIL(&PIPELINE->commands, cmd, entries);
    CMD = cmd;
}
