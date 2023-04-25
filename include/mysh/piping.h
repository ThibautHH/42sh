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
    if (CMD->is_piped) {
        MVFD_STD(PIPEFDS[1], OUT);
        if (close(PIPEFDS[0])) DIE;
    }
    if (CMDPREV && CMDPREV->is_piped)
        MVFD_STD(CMDPREV->outlet, IN);
}

static inline void setup_pipe_shell(mysh_t *context)
{
    if (CMD->is_piped) {
        if (close(PIPEFDS[1])) DIE;
        CMD->outlet = PIPEFDS[0];
    }
    if (CMDPREV && CMDPREV->is_piped && close(CMDPREV->outlet)) DIE;
}

#endif /* !PIPING_H_ */
