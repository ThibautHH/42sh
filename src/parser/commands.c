/*
** EPITECH PROJECT, 2023
** Minishell 2
** File description:
** Command structure management
*/

#include <stdlib.h>

#include "ice/memory.h"

#include "mysh.h"
#include "mysh/parsing.h"

void free_pipelines(mysh_t *context)
{
    pipeline_t *ppl_tmp;
    TAILQ_FOREACH_SAFE(PIPELINE, &context->pipelines, entries, ppl_tmp) {
        command_t *cmd_tmp;
        TAILQ_REMOVE(&context->pipelines, PIPELINE, entries);
        TAILQ_FOREACH_SAFE(CMD, &PIPELINE->commands, entries, cmd_tmp) {
            TAILQ_REMOVE(&PIPELINE->commands, CMD, entries);
            for (size_t i = 0; i < CMDARGC; i++)
                free(CMDARGS[i]);
            free(CMDARGS);
            if (!(CMD->is_builtin))
                free(CMDPATH);
            free(CMD);
        }
        free(PIPELINE);
    }
}

void new_pipeline(mysh_t *context, sequence_mode_t mode)
{
    pipeline_t *ppl = malloc(sizeof(pipeline_t));
    if (!ppl) DIE;
    ppl->mode = mode;
    ppl->command_count = 0;
    TAILQ_INIT(&ppl->commands);
    TAILQ_INSERT_TAIL(&context->pipelines, ppl, entries);
    PIPELINE = ppl;
}

void new_command(mysh_t *context)
{
    command_t *cmd = malloc(sizeof(command_t));
    if (!cmd) DIE;
    cmd->is_piped = 0;
    cmd->argc = 0;
    cmd->args = NULL;
    cmd->is_builtin = 0;
    cmd->command.path = NULL;
    TAILQ_INSERT_TAIL(&PIPELINE->commands, cmd, entries);
    CMD = cmd;
    CMDC++;
}
