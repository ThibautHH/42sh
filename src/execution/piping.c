/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Piping functions
*/

#include "mysh/piping.h"

void feed_redirections(mysh_t *context)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t len = 0;

    if (!IS_REDIR_PIPED)
        return;
    if (CMDRED(STDIN_FILENO).type == REDIR_STRING)
        write(PIPEFDS[1], CMDREDSTR(STDIN_FILENO),
            strlen(CMDREDSTR(STDIN_FILENO)));
    if (CMDRED(STDIN_FILENO).type == REDIR_TIL_LINE)
        while (((len = getline(&line, &size, stdin)) != -1)
            && !(line[len - 1] = '\0')
            && strcmp(line, CMDREDSTR(STDIN_FILENO))) {
            line[len - 1] = '\n';
            write(PIPEFDS[1], line, len);
        }
    if (close(PIPEFDS[1]) || close(PIPEFDS[0]))
        DIE;
}

void setup_redirections(mysh_t *context)
{
    const FILE *STD[3] = {stdin, stdout, stderr};

    for (uc_t i = 0; i < 3; i++)
        if (CMDRED(i).type == REDIR_FILE
            && !freopen(CMDREDFILE(i).name, CMDREDFILE(i).mode,
                (FILE *)STD[i]))
            perror(CMDREDFILE(i).name), DIE;
    if (IS_REDIR_PIPED) {
        if (close(PIPEFDS[1]))
            DIE;
        MVFD_STD(PIPEFDS[0], IN);
    }
}

void setup_pipe_command(mysh_t *context)
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

void setup_pipe_shell(mysh_t *context)
{
    if (CMD->pipe_mode) {
        if (close(PIPEFDS[1]))
            DIE;
        CMD->outlet = PIPEFDS[0];
    }
    if (CMDPREV && CMDPREV->pipe_mode && close(CMDPREV->outlet))
        DIE;
}
