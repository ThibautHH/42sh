/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** run_sequence.c
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "ice/printf.h"

#include "mysh.h"
#include "mysh/builtins.h"
#include "mysh/commands.h"
#include "mysh/parsing.h"
#include "mysh/piping.h"

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

static void wait_for_cmd(mysh_t *context, pid_t pid)
{
    int status;

    if (waitpid(pid, &status, 0) != pid)
        DIE;
    if (WIFSIGNALED(status)) {
        STATUS = WTERMSIG(status) + 128u;
        ice_dprintf(STDERR_FILENO, "%s%s\n", (WTERMSIG(status) == SIGFPE)
            ? "Floating exception" : strsignal(WTERMSIG(status)),
            (WCOREDUMP(status)) ? " (core dumped)" : "");
    } else if (WIFEXITED(status))
        STATUS = WEXITSTATUS(status) ? WEXITSTATUS(status) : STATUS;
}

static pid_t run(mysh_t *context, pid_t *ppl_pids)
{
    if (CMD->is_builtin
        && (CMD == TAILQ_LAST(&PIPELINE->commands, commands_s))) {
            for (size_t i = 0; i < CMDC - 1; i++)
                wait_for_cmd(context, ppl_pids[i]);
            execute_unforked_builtin(context);
            return 0;
        }
    if ((CMD->pipe_mode || IS_REDIR_PIPED) && pipe(PIPEFDS) == -1) DIE;
    pid_t pid = fork();
    if (pid == -1) DIE;
    if (pid == 0) {
        setup_pipe_command(context); setup_redirections(context);
        if (!CMD->is_builtin)
            execute(context);
        BUILTINS[CMDCOMMAND.id].builtin(context);
        free(ppl_pids); QUIT(STATUS);
    }
    feed_redirections(context);
    setup_pipe_shell(context);
    return pid;
}

void run_pipeline(mysh_t *context)
{
    if (!PIPELINE_SHOULD_RUN)
        return;
    STATUS = 0;
    TAILQ_FOREACH(CMD, &PIPELINE->commands, entries)
        if (get_cmd_path(context))
            return;
    pid_t *ppl_pids = malloc(sizeof(pid_t) * CMDC);
    size_t i = 0;
    TAILQ_FOREACH(CMD, &PIPELINE->commands, entries)
        ppl_pids[i++] = run(context, ppl_pids);
    if (ppl_pids[CMDC - 1])
        for (i = 0; i < CMDC; i++)
            wait_for_cmd(context, ppl_pids[i]);
    free(ppl_pids);
}
