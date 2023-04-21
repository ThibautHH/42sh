/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** mysh.h
*/

#ifndef MYSH_H
    #define MYSH_H

    #include <stdbool.h>
    #include <unistd.h>

    #include "ice/macro.h"
    #include "ice/string.h"

    #define IS_END(x) (((x) == '\0') || ((x) == '\n'))
    #define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))

    #define GET_LINE (len = getline(&LINE, &size, stdin))

    #define LINE (context->line)
    #define ENV (context->env)
    #define STATUS (context->status)
    #define EXIT (context->exit)

    #define DIE die(context, 84)

    #define _DWSLEN(s, l) (l > 0 ? l : ice_strlen(s))
    #define DWRITE(fd, s, l) if (write(fd, s, _DWSLEN(s, l)) < 0)DIE
    #define WRITE(s, l) DWRITE(STDOUT_FILENO, s, l)
    #define TTY_WRITE(s, l) tty_write(context, s, l)

typedef struct env_s env_t;

typedef struct mysh_s {
    env_t *env;
    char *line;
    uc_t status;
    bool exit;
} mysh_t;

void mysh(mysh_t *context, char **env);
void prompt(mysh_t *context);
void die(mysh_t *context, uc_t status);

static inline bool is_stdin_tty(mysh_t *context)
{
    int is_tty = isatty(STDIN_FILENO);

    if (is_tty < 0)
        DIE;
    return is_tty;
}

static inline void tty_write(mysh_t *context, const char *str, size_t len)
{
    if (!is_stdin_tty(context))
        return;
    WRITE(str, len);
}

#endif /* !MYSH_H */
