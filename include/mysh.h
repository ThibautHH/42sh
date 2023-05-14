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
    #include <stdio.h>
    #include <unistd.h>

    #include "list.h"
    #include "ice/macro.h"
    #include "ice/string.h"
    #include "list/struct.h"

    #include "mysh/parsing.h"
    #include "mysh/var.h"
    #include "mysh/alias.h"

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
    #define VAR (&(context->vars[type]))
    #define VARQ (&(VAR)->head)
    #define VARC (VAR->count)
    #define PIPEFDS (context->pipefds)
    #define STATUS (context->status)
    #define EXIT (context->exit)
    #define HISTORY (context->history)

    #define ARGV (CMDARGS ? CMDARGS : (char *[]){CMDCMD, NULL})

    #define QUIT(status) (cleanup(context), exit(status))
    #define DIE QUIT(84)

    #define ERRPRINT(a...) if (fprintf(stderr, a) < 0)DIE
    #define PRINT(a...) if (printf(a) < 0)DIE
    #define TTY_WRITE(s) tty_write(context, s)

typedef struct mysh_s {
    var_head_t vars[2];
    alias_head_t alias;
    char *line;
    size_t size;
    ssize_t len;
    TAILQ_HEAD(, pipeline_s) pipelines;
    pipeline_t *current_pipeline;
    command_t *current_command;
    parsing_context_t parsing;
    int pipefds[2];
    uc_t status;
    bool exit;
    list_t *history;
} mysh_t;

void mysh(mysh_t *context, char **env);
void prompt(mysh_t *context);
void cleanup(mysh_t *context);
void run_pipeline(mysh_t *context);
void handle_shebang_invocation(char **argv);
void insert_at_p(mysh_t *context, char *str, size_t len);

static inline bool is_stdin_tty(mysh_t *context)
{
    int is_tty = isatty(STDIN_FILENO);

    if (is_tty < 0)
        DIE;
    return is_tty;
}

static inline void tty_write(mysh_t *context, const char *str)
{
    if (!is_stdin_tty(context))
        return;
    PRINT("%s", str);
}

#endif /* !MYSH_H */
