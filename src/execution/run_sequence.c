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

static const char EXECFMT_ERRFMT[] = "%s: Exec format error. \
Wrong Architecture.\n";

static void execute(mysh_t *context)
{
    char **env = dup_env(context);
    execve(CMDPATH, ARGV, env);
    if (errno == ENOEXEC
        && ice_dprintf(STDERR_FILENO, EXECFMT_ERRFMT, CMDPATH) < 0)
            die(context, 1);
    else
        perror(CMDPATH);
    free(env);
    die(context, 1);
}

static pid_t run(mysh_t *context)
{
    if (CMD->is_builtin
        && (CMD == TAILQ_LAST(&PIPELINE->commands, commands_s))) {
        int stdio[2];
        if ((stdio[0] = dup(STDIN_FILENO)) == -1 ||
            (stdio[1] = dup(STDOUT_FILENO)) == -1) DIE;
        BUILTINS[CMDCOMMAND.id].builtin(context);
        if (dup2(stdio[0], STDIN_FILENO) == -1 ||
            dup2(stdio[1], STDOUT_FILENO) == -1 ||
            close(stdio[0]) == -1 || close(stdio[1]) == -1) DIE;
            return 0;
    }
    pid_t pid = fork();
    if (pid == -1) DIE;
    if (pid == 0) {
        if (!CMD->is_builtin)
            execute(context);
        BUILTINS[CMDCOMMAND.id].builtin(context);
        exit(STATUS);
    }
    return pid;
}

static void wait_for_cmd(mysh_t *context, pid_t pid)
{
    int status;

    if (!pid)
        return;
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

void run_pipeline(mysh_t *context)
{
    TAILQ_FOREACH(CMD, &PIPELINE->commands, entries)
        get_cmd_path(context);
    pid_t *ppl_pids = malloc(sizeof(pid_t) * CMDC);
    size_t i = 0;
    TAILQ_FOREACH(CMD, &PIPELINE->commands, entries)
        ppl_pids[i++] = run(context);
    for (i = 0; i < CMDC; i++)
        wait_for_cmd(context, ppl_pids[i]);
    free(ppl_pids);
}
