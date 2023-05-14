/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** builtin_repeat.c
*/

#include "mysh/commands.h"

static void run_repeat(mysh_t *context, uint64_t nb_iter)
{
    pipeline_t ppl = {0};
    command_t *tmp = CMD;
    command_t cmd = {
        .args = &CMDARGS[2],
        .argc = CMDARGC - 2,
        .pipe_mode = PIPE_NONE,
        .entries = {NULL, NULL},
        .redirections = {{.type = 0},{.type = 0}, {.type = 0}}
    };

    CMD = &cmd;
    TAILQ_INIT(&ppl.commands);
    TAILQ_INSERT_TAIL(&ppl.commands, &cmd, entries);
    get_cmd_path(context);
    for (uint64_t i = 0; i < nb_iter; i++) {
        run(context);
        wait_for_cmd(context);
    }
    CMD = tmp;
}

void builtin_repeat(mysh_t *context)
{
    int64_t nb_iter;
    char *endptr;

    if (CMDARGC < 3) {
        ERRPRINT("repeat: Too few arguments.\n");
        STATUS = 1;
        return;
    }
    nb_iter = strtol(CMDARGS[1], &endptr, 10);
    if (*endptr) {
        ERRPRINT("repeat: Badly formed number.\n");
        STATUS = 1;
        return;
    }
    if (nb_iter > 0)
        run_repeat(context, nb_iter);
}
