/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** execute_binary.c
*/

#include <wait.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "mysh.h"
#include "ice/output.h"
#include "mysh/signals.h"

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

static void handle_execve(char *path, char **av, env_t *env)
{
    struct stat st;

    stat(path, &st);
    if (S_ISDIR(st.st_mode))
        display_error(env, "%s: Permission denied.\n", path);
    else if (execve(path, av, env->env) != -1)
        exit(84);
    if (errno == EACCES)
        display_error(env, "%s: Permission denied.\n", path);
    if (errno == ENOEXEC)
        display_error(env, "%s: Exec format error. Wrong Architecture.\n",
            path);
    exit(0);
}

bool execute_binary(char *path, char **av, env_t *env)
{
    int pid = fork();
    int child_status;

    if (pid == -1)
        return true;
    if (pid == 0)
        handle_execve(path, av, env);
    if (waitpid(pid, &child_status, 0) == -1)
        return true;
    env->status = WEXITSTATUS(child_status)
        + WTERMSIG(child_status) + WCOREDUMP(child_status);
    if (WIFSIGNALED(child_status))
        handle_signal(child_status);
    return false;
}
