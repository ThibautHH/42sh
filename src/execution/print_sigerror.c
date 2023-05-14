/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** print_sigerror.c
*/

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#include "mysh.h"

void print_sigerror(mysh_t *context, int status)
{
    char *coredump = (WCOREDUMP(status)) ? " (core dumped)" : "";
    char *signame = (WTERMSIG(status) == SIGFPE) ?
        "Floating exception" : strsignal(WTERMSIG(status));

    ERRPRINT("%s%s\n", signame, coredump);
}
