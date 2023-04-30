/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Piping definitions
*/

#ifndef PIPING_H_
    #define PIPING_H_

    #include <unistd.h>

    #define MVFD(src, dest) if (dup2(src, dest) == -1 || close(src))DIE
    #define MVFD_STD(src, id) MVFD(src, STD##id##_FILENO)

static inline void setup_pipe_command(mysh_t *context)
{
    if (CMD->pipe_mode) {
        if (CMD->pipe_mode & PIPE_OUT)
            MVFD_STD(PIPEFDS[1], OUT);
        if (CMD->pipe_mode & PIPE_ERR)
            MVFD_STD(PIPEFDS[1], ERR);
        if (close(PIPEFDS[0])) DIE;
    }
    if (CMDPREV && CMDPREV->pipe_mode)
        MVFD_STD(CMDPREV->outlet, IN);
}

static inline void setup_pipe_shell(mysh_t *context)
{
    if (CMD->pipe_mode) {
        if (close(PIPEFDS[1])) DIE;
        CMD->outlet = PIPEFDS[0];
    }
    if (CMDPREV && CMDPREV->pipe_mode && close(CMDPREV->outlet)) DIE;
}

#endif /* !PIPING_H_ */
