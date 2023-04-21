/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** execute_binary.c
*/

#include <wait.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "mysh/env.h"
#include "ice/output.h"
#include "mysh/signals.h"
#include "mysh/miscellaneous.h"

static void handle_signal(int child_status)
{
    int sig = WTERMSIG(child_status);

    for (ul_t i = 0 ; signals[i].name ; i++)
        if (signals[i].sig == sig) {
            ice_puts(signals[i].name);
            break;
        }
    if (WCOREDUMP(child_status))
        write(1, " (core dumped)\n", 15);
    else
        write(1, "\n", 1);
}

static void handle_execve(char *path, char **av, mysh_t *context)
{
    struct stat st;

    stat(path, &st);
    if (S_ISDIR(st.st_mode))
        display_error(context, "%s: Permission denied.\n", path);
    else if (execve(path, av, ENV->env) != -1)
        exit(84);
    if (errno == EACCES)
        display_error(context, "%s: Permission denied.\n", path);
    if (errno == ENOEXEC)
        display_error(context, "%s: Exec format error. Wrong Architecture.\n",
            path);
    exit(0);
}

bool execute_binary(char *path, char **av, mysh_t *context)
{
    int pid = fork();
    int child_status;

    if (pid == -1)
        return true;
    if (pid == 0)
        handle_execve(path, av, context);
    if (waitpid(pid, &child_status, 0) == -1)
        return true;
    STATUS = WEXITSTATUS(child_status)
        + WTERMSIG(child_status) + WCOREDUMP(child_status);
    if (WIFSIGNALED(child_status))
        handle_signal(child_status);
    return false;
}
