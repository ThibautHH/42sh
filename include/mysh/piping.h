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

    #define MVFD(src, dest) if (dup2(src, dest) == -1 || close(src)) DIE
    #define MVFD_STD(src, id) MVFD(src, STD##id##_FILENO)

static inline void feed_redirections(mysh_t *context)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t len = 0;

    if (CMDRED(STDIN_FILENO).type != REDIR_STRING
        && CMDRED(STDIN_FILENO).type != REDIR_TIL_LINE)
        return;
    if (CMDRED(STDIN_FILENO).type == REDIR_STRING)
        write(PIPEFDS[1], CMDREDSTR(STDIN_FILENO),
            strlen(CMDREDSTR(STDIN_FILENO)));
    if (CMDRED(STDIN_FILENO).type == REDIR_TIL_LINE)
        while (((len = getline(&line, &size, stdin)) != -1)
            && strcmp(line, CMDREDSTR(STDIN_FILENO)))
            write(PIPEFDS[1], line, len);
    if (close(PIPEFDS[1]) || close(PIPEFDS[0]))
        DIE;
}

static inline void setup_redirections(mysh_t *context)
{
    const FILE *STD[3] = {stdin, stdout, stderr};

    for (uc_t i = 0, closed = 0; i < 3; i++) {
        if (CMDRED(i).type && !(closed++) && close(PIPEFDS[1]))
            DIE;
        if (CMDRED(i).type == REDIR_FILE
            && !freopen(CMDREDFILE(i).name, CMDREDFILE(i).mode,
                (FILE *)STD[i]))
            perror(CMDREDFILE(i).name), DIE;
    }
    if (CMDRED(STDIN_FILENO).type == REDIR_STRING
        || CMDRED(STDIN_FILENO).type == REDIR_TIL_LINE)
        MVFD_STD(PIPEFDS[0], IN);
}

static inline void setup_pipe_command(mysh_t *context)
{
    if (CMD->pipe_mode
        && ((CMD->pipe_mode & PIPE_OUT
        && dup2(PIPEFDS[1], STDOUT_FILENO) == -1)
        || (CMD->pipe_mode & PIPE_ERR
        && dup2(PIPEFDS[1], STDERR_FILENO) == -1)
        || close(PIPEFDS[1]) || close(PIPEFDS[0])))
        DIE;
    if (CMDPREV && CMDPREV->pipe_mode)
        MVFD_STD(CMDPREV->outlet, IN);
}

static inline void setup_pipe_shell(mysh_t *context)
{
    if (CMD->pipe_mode) {
        if (close(PIPEFDS[1]))
            DIE;
        CMD->outlet = PIPEFDS[0];
    }
    if (CMDPREV && CMDPREV->pipe_mode && close(CMDPREV->outlet))
        DIE;
}

#endif /* !PIPING_H_ */
