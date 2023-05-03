/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** mysh.h
*/

#ifndef MYSH_H
    #define MYSH_H

    #include <sys/queue.h>

    #include <stdbool.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <stdio.h>

    #include "ice/macro.h"
    #include "ice/array.h"
    #include "ice/string.h"
    #include "ice/output.h"
    #include "ice/printf.h"
    #include "list.h"
    #include "list/struct.h"
    #include "ice/string.h"

    #include "mysh/history.h"
    #include "mysh/env.h"

    #define IS_END(x) (((x) == '\0') || ((x) == '\n'))
    #define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))
    #define _SC ;
    #define _TQFSIT_(v, f, t)  ((t) = TAILQ_NEXT(v, f), 1)_SC (v) = (t)
    #define _TQFSIT(v, h, f, t) (v) && _TQFSIT_(v, f, t)
    #define _TQFS(v, h, f, t) (v) = TAILQ_FIRST(h)_SC _TQFSIT(v, h, f, t)
    #define	TAILQ_FOREACH_SAFE(v, h, f, t) for (_TQFS(v, h, f, t))

    #define GET_LINE (len = getline(&LINE, &size, stdin))

    #define LINE (context->line)
    #define ENV (&(context->env))
    #define ENVQ (&(ENV)->head)
    #define ENVC (ENV->count)
    #define STATUS (context->status)
    #define EXIT (context->exit)
    #define HISTORY (context->history)

    #define DIE die(context, 84)
    #include "ice/array.h"
    #include "ice/string.h"
    #include "ice/output.h"
    #include "ice/printf.h"
    #include "list.h"
    #include "list/struct.h"

    #define _DWSLEN(s, l) (l > 0 ? l : ice_strlen(s))
    #define DWRITE(fd, s, l) if (write(fd, s, _DWSLEN(s, l)) < 0)DIE
    #define WRITE(s, l) DWRITE(STDOUT_FILENO, s, l)
    #define TTY_WRITE(s, l) tty_write(context, s, l)

typedef struct mysh_s {
    env_head_t env;
    char *line;
    uc_t status;
    bool exit;
    int ch;
    list_t *history;
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

#endif
