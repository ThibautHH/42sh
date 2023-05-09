/*
** EPITECH PROJECT, 2023
** Minishell 2
** File description:
** Parsing definitions
*/

#ifndef PARSING_H_
    #define PARSING_H_

    #include <stddef.h>
    #include <stdint.h>

    #include <sys/queue.h>

    #include "ice/string.h"

    #include "mysh/builtins.h"

    #define PPLSEPC 7

    #define IS_SPC(c) ((c) == ' ' || (c) == '\t')
    #define IS_QUOTE(c) ((c) == '"' || (c) == '\'' || (c) == '`')
    #define IS_REDIR(c) ((c) == '<' || (c) == '>')
    #define IS_CHAR_ESCAPED (is_char_escaped(context))
    #define TO_NEXT_TOKEN (to_next_token(context))
    #define TO_TOKEN_END (to_token_end(context))
    #define IS_ESC_NL (*P == '\n' && IS_CHAR_ESCAPED)
    #define IS_SEPARATOR ((IS_SPC(*P) && !IS_CHAR_ESCAPED) || IS_ESC_NL)
    #define IS_PPLSEP (get_ppl_separator(context), PPLSEP >= 0)
    #define PPLSEPS(i) PPL_SEPARATORS[i]
    #define IS_PPLSEP_STR (!ice_strncmp2(P, PPLSEPS(i).sep, PPLSEPS(i).len))

    #define C_PS_SM2 (PPLSEP == PPLSEP_OR) ? SEQ_OR
    #define COND_PPLSEP_SEQMODE (PPLSEP == PPLSEP_AND) ? SEQ_AND : C_PS_SM2

    #define PIPELINE (context->current_pipeline)

    #define CMD (PIPELINE->current_command)
    #define CMDPREV TAILQ_PREV(CMD, commands_s, entries)
    #define CMDARGS (CMD->args)
    #define CMDCMD CMDARGS[0]
    #define CMDCOMMAND (CMD->command)
    #define CMDPID (CMD->pid)
    #define CMDRED(i) (CMD->redirections[i])
    #define CMDREDFILE(i) (CMDRED(i).target.file)
    #define CMDREDSTR(i) (CMDRED(i).target.string)
    #define CMDPATH (CMDCOMMAND.path)
    #define CMDARGC (CMD->argc)
    #define CMDARGSZ (CMDARGC * sizeof(char *))

    #define PARSE_RED(d) (parse_##d##put_redirection(context), 1)
    #define SET_PARSE_ERR PARSING_ERROR = (STATUS = 1)
    #define PARSE_ERR(s, l) ({DWRITE(2, s, l); SET_PARSE_ERR; return;})

    #define PREP_DUP_ARG ({char t, *b; b = P; TO_TOKEN_END; t = *P; *P = '\0'
    #define DUP_ARG(d) PREP_DUP_ARG; d = strdup(b); if (!d) DIE; *P = t;})

    #define PARSING (context->parsing)
    #define P (PARSING.p)
    #define S (PARSING.s)
    #define PPLSEP (PARSING.pplsep)
    #define LAST_PPLSEP (PARSING.last_pplsep)
    #define PARSING_ERROR (PARSING.error)

typedef enum required_sides_e {
    RS_NONE = 0b001,
    RS_LEFT = 0b010,
    RS_RIGHT = 0b100,
    RS_BOTH = 0b110
} required_sides_t;

typedef enum pipeline_separator_e {
    PPLSEP_NONE = -1,
    PPLSEP_SEMICOLON,
    PPLSEP_AND,
    PPLSEP_AMPERSAND,
    PPLSEP_OR,
    PPLSEP_PIPE_ERROUT,
    PPLSEP_PIPE,
    PPLSEP_END
} pplsep_t;

typedef enum sequence_mode_e {
    SEQ_NONE,
    SEQ_AND,
    SEQ_OR
} sequence_mode_t;

typedef enum pipe_type_e {
    PIPE_NONE,
    PIPE_OUT,
    PIPE_ERR,
    PIPE_ERROUT
} pipe_type_t;

typedef enum redirection_type_e {
    REDIR_NONE = 0,
    REDIR_FILE,
    REDIR_TIL_LINE,
    REDIR_STRING
} red_type_t;

typedef struct redirection_s {
    union {
        struct {
            char *name;
            char mode[3];
        } file;
        char *string;
    } target;
    red_type_t type;
} redirection_t;

typedef struct command_s {
    union {
        char *path;
        builtin_t id;
    } command;
    pid_t pid;
    _Bool is_builtin;
    char **args;
    size_t argc;
    pipe_type_t pipe_mode;
    int outlet;
    redirection_t redirections[3];
    TAILQ_ENTRY(command_s) entries;
} command_t;

typedef struct pipeline_s {
    sequence_mode_t mode;
    TAILQ_HEAD(commands_s, command_s) commands;
    command_t *current_command;
    TAILQ_ENTRY(pipeline_s) entries;
} pipeline_t;

typedef struct parsing_context_s {
    pplsep_t pplsep, last_pplsep;
    char *p, *s;
    _Bool error;
} parsing_context_t;

static const struct {
    char *sep;
    size_t len;
    required_sides_t sides;
} PPL_SEPARATORS[PPLSEPC] = {
    { ";", 1, RS_NONE },
    { "&&", 2, RS_NONE | RS_RIGHT },
    { "&", 1, RS_NONE },
    { "||", 2, RS_BOTH },
    { "|&", 2, RS_BOTH },
    { "|", 1, RS_BOTH },
    { "\n", 1, RS_NONE }
};

_Bool parse_command_line(mysh_t *context);

#endif /* !PARSING_H_ */
