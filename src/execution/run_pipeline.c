/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** run_sequence.c
*/

#include <errno.h>
#include <malloc.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "mysh/piping.h"
#include "mysh/commands.h"

static void execute(mysh_t *context)
{
    char **env = dup_env(context);

    execve(CMDPATH, ARGV, env);
    if (errno == ENOEXEC) {
        if (fprintf(stderr,
            "%s: Exec format error. Wrong Architecture.\n", CMDPATH) < 0)
            DIE;
    } else
        if (fprintf(stderr, "%s: Permission denied.\n", CMDPATH) < 0)
            DIE;
    free(env);
    QUIT(1);
}

static void execute_unforked_builtin(mysh_t *context)
{
    int stdio[] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

    if (stdio[0] == -1 || stdio[1] == -1)
        DIE;
    if (CMDPREV && CMDPREV->pipe_mode)
        MVFD_STD(CMDPREV->outlet, IN);
    BUILTINS[CMDCOMMAND.id].builtin(context);
    MVFD_STD(stdio[0], IN);
    MVFD_STD(stdio[1], OUT);
}

static void wait_for_cmd(mysh_t *context)
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
        char *signame = (WTERMSIG(status) == SIGFPE) ? "Floating exception" : strsignal(WTERMSIG(status));
        char *coredump = (WCOREDUMP(status)) ? " (core dumped)" : "";
        if (fprintf(stderr, "%s%s\n", signame, coredump) < 0)
            DIE;
    } else if (WIFEXITED(status) && WEXITSTATUS(status))
        STATUS = WEXITSTATUS(status);
}

static void run(mysh_t *context)
{
    command_t *cmd;

    if (CMD->is_builtin
        && (CMD == TAILQ_LAST(&PIPELINE->commands, commands_s))) {
        CMDPID = -1;
        TAILQ_FOREACH(cmd, &PIPELINE->commands, entries)
            wait_for_cmd(context);
        execute_unforked_builtin(context);
        return;
        }
    if ((CMD->pipe_mode || IS_REDIR_PIPED) && pipe(PIPEFDS) == -1)
        DIE;
    CMDPID = fork();
    if (CMDPID == -1)
        DIE;
    if (CMDPID == 0) {
        setup_pipe_command(context);
        setup_redirections(context);
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
