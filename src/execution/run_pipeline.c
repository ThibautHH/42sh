/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** run_sequence.c
*/

#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ice/printf.h"

#include "mysh.h"
#include "mysh/piping.h"
#include "mysh/commands.h"

static const char EXECFMT_ERRFMT[] = "%s: Exec format error. \
Wrong Architecture.\n";

static void execute(mysh_t *context)
{
    char **env = dup_env(context);
    execve(CMDPATH, ARGV, env);
    if (errno == ENOEXEC)
        ice_dprintf(STDERR_FILENO, EXECFMT_ERRFMT, CMDPATH);
    else
        ice_dprintf(STDERR_FILENO, "%s: Permission denied.\n", CMDPATH);
    free(env);
    QUIT(1);
}

static void execute_unforked_builtin(mysh_t *context)
{
    int stdio[2];
    if ((stdio[0] = dup(STDIN_FILENO)) == -1
        || (stdio[1] = dup(STDOUT_FILENO)) == -1)
        DIE;
    if (CMDPREV && CMDPREV->pipe_mode)
        MVFD_STD(CMDPREV->outlet, IN);
    BUILTINS[CMDCOMMAND.id].builtin(context);
    MVFD_STD(stdio[0], IN);
    MVFD_STD(stdio[1], OUT);
}

void wait_for_cmd(mysh_t *context)
{
    int status;

    if (CMDPID == -1)
        return;
    if (waitpid(CMDPID, &status, 0) != CMDPID)
        DIE;
    if (WIFSIGNALED(status)) {
        STATUS = WTERMSIG(status) + 128u;
        if (WTERMSIG(status) == SIGPIPE && CMD->pipe_mode)
            return;
        ice_dprintf(STDERR_FILENO, "%s%s\n", (WTERMSIG(status) == SIGFPE)
            ? "Floating exception" : strsignal(WTERMSIG(status)),
            (WCOREDUMP(status)) ? " (core dumped)" : "");
    } else if (WIFEXITED(status))
        STATUS = WEXITSTATUS(status) ? WEXITSTATUS(status) : STATUS;
}

void run(mysh_t *context)
{
    if (CMD->is_builtin
        && (CMD == TAILQ_LAST(&PIPELINE->commands, commands_s))) {
            command_t *cmd; CMDPID = -1;
            TAILQ_FOREACH(cmd, &PIPELINE->commands, entries)
                wait_for_cmd(context);
            execute_unforked_builtin(context);
            return;
        }
    if ((CMD->pipe_mode || IS_REDIR_PIPED) && pipe(PIPEFDS) == -1) DIE;
    CMDPID = fork();
    if (CMDPID == -1) DIE;
    if (CMDPID == 0) {
        setup_pipe_command(context); setup_redirections(context);
        if (!CMD->is_builtin)
            execute(context);
        BUILTINS[CMDCOMMAND.id].builtin(context);
        QUIT(STATUS);
    }
    feed_redirections(context);
    setup_pipe_shell(context);
}

void run_pipeline(mysh_t *context)
{
    if (!PIPELINE_SHOULD_RUN)
        return;
    STATUS = 0;
    TAILQ_FOREACH(CMD, &PIPELINE->commands, entries)
        if (get_cmd_path(context))
            return;
    TAILQ_FOREACH(CMD, &PIPELINE->commands, entries)
        run(context);
    if (TAILQ_LAST(&PIPELINE->commands, commands_s)->pid != -1)
        TAILQ_FOREACH(CMD, &PIPELINE->commands, entries)
            wait_for_cmd(context);
}
