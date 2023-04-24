/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_pipe.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ice/array.h"
#include "ice/string.h"
#include "mysh/redirection.h"
#include "mysh/miscellaneous.h"

static bool execute(char *sequence, mysh_t *context, int pid)
{
    char **av;
    redirs_t redirs = {0};

    if (set_redirection(&redirs, sequence, context))
        return true;
    av = get_argument(sequence);
//    if (!av || search_function(av, context))
//        return true;
    if (pid > 0 && waitpid(pid, NULL, 0) == -1)
        return false;
    if (unset_redirection(&redirs))
        return true;
    ice_free_array((void **)av);
    if (pid > 0)
        exit(0);
    return false;
}

static int handle_fork(int *pipefd)
{
    int pid = fork();

    if (pid == -1)
        return -1;
    if (pid == 0)
        return (close(pipefd[0]) == -1
            || dup2(pipefd[1], STDOUT_FILENO) == -1) ? -1 : pid;
    return (close(pipefd[1]) == -1
        || dup2(pipefd[0], STDIN_FILENO) == -1) ? -1 : pid;
}

static bool set_pipe(int *pipefd, char *line, mysh_t *context, int *pid)
{
    if (pipe(pipefd) == -1)
        return true;
    *pid = handle_fork(pipefd);
    if (*pid == -1)
        return true;
    return (*pid != 0) ? execute(line, context, *pid) : false;
}

bool handle_pipe(char *line, mysh_t *context)
{
    char **sequence = ice_strsplit(line, "|");
    int len = (int)ice_array_len((void **)sequence);
    int pid = 0;
    int pipefd[2] = {0};
    int out = 0;

    if (len > 1)
        out = dup(STDOUT_FILENO);
    if (!sequence || out == -1)
        return true;
    for (int i = len - 1; 0 < i; i--) {
        if (set_pipe(pipefd, sequence[i], context, &pid))
            return true;
        if (pid != 0)
            break;
    }
    if (execute(sequence[0], context, pid))
        return true;
    ice_free_array((void **)sequence);
    return len > 1 && dup2(out, STDOUT_FILENO) == -1;
}
