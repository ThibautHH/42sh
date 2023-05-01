/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** parse_command_line.c
*/

#include "ice/memory.h"
#include "ice/string.h"

#include "mysh.h"
#include "mysh/commands.h"
#include "mysh/parsing.h"
#include "mysh/parsing_functions.h"

static void tokenize(mysh_t *context)
{
    for (; *P && !IS_PPLSEP; TO_NEXT_TOKEN) {
        CMDARGC++;
        CMDARGS = ice_realloc2(CMDARGS, CMDARGSZ, CMDARGSZ + sizeof(char *));
        if (!CMDARGS) DIE;
        char *token = P, tmp;
        TO_TOKEN_END;
        tmp = *P; *P = '\0';
        CMDARGS[CMDARGC - 1] = ice_strdup(token);
        if (!CMDARGS[CMDARGC - 1]) DIE;
        *P = tmp;
    }
    CMDARGS[CMDARGC] = NULL;
}

static void handle_pplsep(mysh_t *context, size_t *separator_count)
{
    if (((++(*separator_count) >= 2 && PPLSEPS(PPLSEP).sides & RS_LEFT)
        || (((PPLSEPS(LAST_PPLSEP).sides & RS_RIGHT)
            && (PPLSEPS(LAST_PPLSEP).sides & RS_NONE)
            ? *separator_count == 2
            : *separator_count >= 2)))) {
        DWRITE(STDERR_FILENO, "Invalid null command.\n", 22);
        PARSING_ERROR = (STATUS = 1);
        return;
    }
    switch (PPLSEP) {
    case PPLSEP_PIPE: CMD->pipe_mode = PIPE_OUT; break;
    case PPLSEP_PIPE_ERROUT: CMD->pipe_mode = PIPE_ERROUT; break;
    default: new_pipeline(context, (COND_PPLSEP_SEQMODE : SEQ_NONE));
    }
    P += PPLSEPS(PPLSEP).len;
}

_Bool parse_command_line(mysh_t *context)
{
    size_t separator_count = 1;
    P = LINE, S = LINE,
    PARSING_ERROR = 0,
    PPLSEP = PPLSEP_NONE, LAST_PPLSEP = PPLSEP_END;
    TO_NEXT_TOKEN;
    if (!*P)
        return 1;
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
