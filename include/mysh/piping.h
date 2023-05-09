/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Piping definitions
*/

#ifndef PIPING_H_
    #define PIPING_H_

    #include <unistd.h>
    #include <stdio.h>

    #include "mysh.h"

    #define INRDT (CMDRED(STDIN_FILENO).type)
    #define IS_REDIR_PIPED (INRDT == REDIR_STRING || INRDT == REDIR_TIL_LINE)

    #define MVFD(src, dest) if (dup2(src, dest) == -1 || close(src)) DIE
    #define MVFD_STD(src, id) MVFD(src, STD##id##_FILENO)

void feed_redirections(mysh_t *context);
void setup_redirections(mysh_t *context);
void setup_pipe_command(mysh_t *context);
void setup_pipe_shell(mysh_t *context);

#endif /* !PIPING_H_ */
