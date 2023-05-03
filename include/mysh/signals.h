/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** signal.h
*/

#ifndef MINISHELL1_SIGNAL_H
    #define MINISHELL1_SIGNAL_H

    #include <unistd.h>
    #include <signal.h>

//
// Structs
//

typedef struct signal_s {
    int sig;
    char *name;
} signal_t;

const signal_t signals[] = {
        {SIGABRT, "Aborted"},
        {SIGFPE, "Floating exception"},
        {SIGILL, "Illegal instruction"},
        {SIGINT, "Interrupt"},
        {SIGSEGV, "Segmentation fault"},
        {SIGTERM, "Terminated"},
        {SIGQUIT, "Quit"},
        {SIGKILL, "Killed"},
        {SIGALRM, "Alarm clock"},
        {SIGBUS, "Bus error"},
        {SIGCHLD, "Child exited"},
        {SIGCONT, "Continued"},
        {SIGSTOP, "Stopped"},
        {SIGTSTP, "Stopped"},
        {SIGTTIN, "Stopped"},
        {SIGTTOU, "Stopped"},
        {SIGUSR1, "User defined signal 1"},
        {SIGUSR2, "User defined signal 2"},
        {SIGPIPE, "Broken pipe"},
        {SIGPROF, "Profiling timer expired"},
        {SIGSYS, "Bad system call"},
        {SIGTRAP, "Trace/breakpoint trap"},
        {SIGURG, "Urgent I/O condition"},
        {SIGVTALRM, "Virtual timer expired"},
        {SIGXCPU, "CPU time limit exceeded"},
        {SIGXFSZ, "File size limit exceeded"},
        {0, NULL}
};

#endif //MINISHELL1_SIGNAL_H
