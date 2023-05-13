/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** run_builtins.c
*/

#include "mysh/piping.h"
#include "mysh/commands.h"

static void execute_unforked_builtin(mysh_t *context)
{
    int stdio[] = {dup(STDIN_FILENO), dup(STDOUT_FILENO), dup(STDERR_FILENO)};

    if (stdio[0] == -1 || stdio[1] == -1 || stdio[2] == -1)
        DIE;
    if (CMDPREV && CMDPREV->pipe_mode)
        MVFD_STD(CMDPREV->outlet, IN);
    setup_redirections(context);
    BUILTINS[CMDCOMMAND.id].builtin(context);
    MVFD_STD(stdio[0], IN);
    MVFD_STD(stdio[1], OUT);
    MVFD_STD(stdio[2], ERR);
    feed_redirections(context);
}

bool run_builtins(mysh_t *context)
{
    command_t *cmd;

    if (CMD->is_builtin
        && (CMD == TAILQ_LAST(&PIPELINE->commands, commands_s))) {
        CMDPID = -1;
        TAILQ_FOREACH(cmd, &PIPELINE->commands, entries)
        wait_for_cmd(context);
        execute_unforked_builtin(context);
        return true;
    }
    return false;
}
