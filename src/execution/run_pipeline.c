/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** run_sequence.c
*/

#include <errno.h>
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
        ERRPRINT("%s: Exec format error. Wrong Architecture.\n", CMDPATH);
    } else
        ERRPRINT("%s: %s.\n", CMDPATH, strerror(errno));
    free(env);
    QUIT(1);
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
        print_sigerror(context, status);
    } else if (WIFEXITED(status) && WEXITSTATUS(status))
        STATUS = WEXITSTATUS(status);
}

void run(mysh_t *context)
{
    if (run_unforked_builtin(context))
        return;
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
