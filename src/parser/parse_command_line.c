/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parse_command_line.c
*/

#include <string.h>

#include "mysh/commands.h"
#include "mysh/parsing_functions.h"

static void parse_output_redirection(mysh_t *context)
{
    redirection_t red = {.type = REDIR_FILE, .target.file.mode = "w"};
    uc_t target = STDOUT_FILENO;

    P++;
    if (!IS_CHAR_ESCAPED && *P == '>')
        *(red.target.file.mode) = 'a', P++;
    if (!IS_CHAR_ESCAPED && *P == '&')
        target = STDERR_FILENO, P++;
    if (CMDRED(target).type != REDIR_NONE)
        PARSE_ERR("Ambiguous output redirect.\n");
    else if (IS_SEPARATOR)
        TO_NEXT_TOKEN;
    DUP_ARG(red.target.file.name);
    CMDRED(target) = red;
}

static void parse_input_redirection(mysh_t *context)
{
    redirection_t red = {.type = REDIR_FILE, .target.file.mode = "r\0"};
    char **value;

    P++;
    if (CMDRED(STDIN_FILENO).type != REDIR_NONE)
        PARSE_ERR("Ambiguous input redirect.\n");
    if (!IS_CHAR_ESCAPED && *P == '>')
        (red.target.file.mode)[1] = '+', P++;
    else if (!IS_CHAR_ESCAPED && *P == '<')
        red.type = REDIR_TIL_LINE + (P[1] == '<'), P += 1 + (P[1] == '<');
    if (IS_SEPARATOR)
        TO_NEXT_TOKEN;
    value = (red.type == REDIR_FILE) ?
        &red.target.file.name : &red.target.string;
    DUP_ARG(*value);
    if (red.type == REDIR_FILE && red.target.file.mode[1]
        && access(*value, F_OK))
        *(red.target.file.mode) = 'w';
    CMDRED(STDIN_FILENO) = red;
}

static void tokenize(mysh_t *context)
{
    for (; !PARSING_ERROR && *P && !IS_PPLSEP; TO_NEXT_TOKEN) {
        if ((*P == '<' && PARSE_RED(in)) || (*P == '>' && PARSE_RED(out)))
            continue;
        CMDARGC++;
        CMDARGS = realloc(CMDARGS, CMDARGSZ);
        if (!CMDARGS)
            DIE;
        DUP_ARG(CMDARGS[CMDARGC - 1]);
        do_globbing(context);
    }
    CMDARGS[CMDARGC] = NULL;
}

static void handle_pplsep(mysh_t *context, size_t *separator_count)
{
    if (((++(*separator_count) >= 2 && PPLSEPS(PPLSEP).sides & RS_LEFT)
        || (((PPLSEPS(LAST_PPLSEP).sides & RS_RIGHT)
            && (PPLSEPS(LAST_PPLSEP).sides & RS_NONE)
            ? *separator_count == 2 : *separator_count >= 2))))
        PARSE_ERR("Invalid null command.\n");
    P += PPLSEPS(PPLSEP).len;
    if (CMDPREV && CMDPREV->pipe_mode && CMDRED(STDIN_FILENO).type)
        PARSE_ERR("Ambiguous input redirect.\n");
    switch (PPLSEP) {
        case PPLSEP_PIPE: CMD->pipe_mode = PIPE_OUT; break;
        case PPLSEP_PIPE_ERROUT: CMD->pipe_mode = PIPE_ERROUT; break;
        case PPLSEP_END: return;
        default:
            new_pipeline(context, (COND_PPLSEP_SEQMODE : SEQ_NONE)); return;
    }
    if (CMD->pipe_mode & PIPE_OUT && CMDRED(STDOUT_FILENO).type)
        PARSE_ERR("Ambiguous output redirect.\n");
    if (CMD->pipe_mode & PIPE_ERR && CMDRED(STDERR_FILENO).type)
        PARSE_ERR("Ambiguous error output redirect.\n");
}

bool parse_command_line(mysh_t *context)
{
    size_t separator_count = 1;

    P = LINE;
    S = LINE;
    PARSING_ERROR = 0;
    PPLSEP = PPLSEP_NONE;
    LAST_PPLSEP = PPLSEP_END;
    TO_NEXT_TOKEN;
    if (!*P)
        return true;
    new_pipeline(context, SEQ_NONE);
    for (; !PARSING_ERROR && *P; TO_NEXT_TOKEN)
        if (!IS_PPLSEP) {
            new_command(context);
            tokenize(context);
            separator_count = 0;
        } else
            handle_pplsep(context, &separator_count);
    return PARSING_ERROR;
}
