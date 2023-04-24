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

    #define PPLSEPC 6

    #define IS_SPC(c) ((c) == ' ' || (c) == '\t')
    #define IS_QUOTE(c) ((c) == '"' || (c) == '\'' || (c) == '`')
    #define IS_CHAR_ESCAPED (is_char_escaped(context))
    #define TO_NEXT_TOKEN (to_next_token(context))
    #define TO_TOKEN_END (to_token_end(context))
    #define _IS_SEP (*P == '\n' && IS_CHAR_ESCAPED)
    #define IS_SEPARATOR ((IS_SPC(*P) && !IS_CHAR_ESCAPED) || _IS_SEP)
    #define IS_PPLSEP (get_ppl_separator(context), PPLSEP >= 0)
    #define _PS(i) PPL_SEPARATORS[i]
    #define _IS_PPLSEP_STR (!ice_strncmp2(P, _PS(i).sep, _PS(i).len))

    #define _C_PS_SM (PPLSEP == PPLSEP_OR) ? SEQ_OR
    #define COND_PPLSEP_SEQMODE (PPLSEP == PPLSEP_AND) ? SEQ_AND : _C_PS_SM

    #define PIPELINE (context->current_pipeline)
    #define CMDC (PIPELINE->command_count)

    #define CMD (PIPELINE->current_command)
    #define CMDPREV TAILQ_PREV(CMD, commands_s, entries)
    #define ISCMDPIPED (CMD->is_piped)
    #define CMDARGS (CMD->args)
    #define CMDCMD CMDARGS[0]
    #define CMDCOMMAND (CMD->command)
    #define CMDPATH (CMDCOMMAND.path)
    #define CMDARGC (CMD->argc)
    #define CMDARGSZ (CMDARGC * sizeof(char *))

    #define PARSING (context->parsing)
    #define P (PARSING.p)
    #define S (PARSING.s)
    #define PPLSEP (PARSING.pplsep)
    #define LAST_PPLSEP (PARSING.last_pplsep)

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
    PPLSEP_PIPE,
    PPLSEP_END
} pplsep_t;

typedef enum sequence_mode_e {
    SEQ_NONE,
    SEQ_AND,
    SEQ_OR
} sequence_mode_t;

typedef struct command_s {
    union {
        char *path;
        builtin_t id;
    } command;
    _Bool is_builtin;
    char **args;
    size_t argc;
    _Bool is_piped;
    int outlet;
    TAILQ_ENTRY(command_s) entries;
} command_t;

typedef struct pipeline_s {
    sequence_mode_t mode;
    TAILQ_HEAD(commands_s, command_s) commands;
    command_t *current_command;
    size_t command_count;
    TAILQ_ENTRY(pipeline_s) entries;
} pipeline_t;

typedef struct parsing_context_s {
    pplsep_t pplsep, last_pplsep;
    char *p, *s;
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
    { "|", 1, RS_BOTH },
    { "\0", 1, RS_NONE }
};

_Bool parse_command_line(mysh_t *context);

#endif /* !PARSING_H_ */
