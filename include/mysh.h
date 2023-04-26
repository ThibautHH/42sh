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
    #include <stdlib.h>
    #include <unistd.h>

    #include "ice/macro.h"
    #include "ice/string.h"

    #include "mysh/parsing.h"
    #include "mysh/env.h"
    #include "mysh/alias.h"

    #include "list.h"

    #define IS_END(x) (((x) == '\0') || ((x) == '\n'))
    #define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))
    #define ISWS(x) (x) == '\v' || (x) == '\f' || (x) == '\r' || (x) == '\n'
    #define IS_WHITESPACE(x) ((x) == ' ' || (x) == '\t' || ISWS(x))
    #define SMCLN ;
    #define TQFSIT(v, f, t)   (v) = (t)
    #define TQFSCND2(v, f, t) ((t) = TAILQ_NEXT(v, f), 1)
    #define TQFSCND(v, h, f, t) (v) && TQFSCND2(v, f, t)SMCLN TQFSIT(v, f, t)
    #define TQFS(v, h, f, t) (v) = TAILQ_FIRST(h)SMCLN TQFSCND(v, h, f, t)
    #define	TAILQ_FOREACH_SAFE(v, h, f, t) for (TQFS(v, h, f, t))

    #define GET_LINE (LEN = getline(&LINE, &LINESZ, stdin))
    #define LINE_ITERATION (prompt(context), free_pipelines(context), errno = 0)
    #define PPLMIS(t) (PIPELINE->mode == SEQ_##t)
    #define PPLCNDLMODES (PPLMIS(AND) && !STATUS) || (PPLMIS(OR) && STATUS)
    #define PIPELINE_SHOULD_RUN (PPLMIS(NONE) || PPLCNDLMODES)

    #define LINE (context->line)
    #define LINESZ (context->size)
    #define LEN (context->len)
    #define ENV (&(context->env))
    #define ENVQ (&(ENV)->head)
    #define ENVC (ENV->count)
    #define PIPEFDS (context->pipefds)
    #define STATUS (context->status)
    #define EXIT (context->exit)

    #define ARGV (CMDARGS ? CMDARGS : (char *[]){CMDCMD, NULL})

    #define QUIT(status) (cleanup(context), exit(status))
    #define DIE QUIT(84)

    #define DW_STRLEN(s, l) (l > 0 ? l : ice_strlen(s))
    #define DWRITE(fd, s, l) if (write(fd, s, DW_STRLEN(s, l)) < 0)DIE
    #define WRITE(s, l) DWRITE(STDOUT_FILENO, s, l)
    #define TTY_WRITE(s, l) tty_write(context, s, l)

typedef struct mysh_s {
    env_head_t env;
    alias_head_t alias;
    char *line;
    size_t size;
    ssize_t len;
    TAILQ_HEAD(, pipeline_s) pipelines;
    pipeline_t *current_pipeline;
    parsing_context_t parsing;
    int pipefds[2];
    uc_t status;
    bool exit;
} mysh_t;

void mysh(mysh_t *context, char **env);
void prompt(mysh_t *context);
void cleanup(mysh_t *context);
void run_pipeline(mysh_t *context);

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
