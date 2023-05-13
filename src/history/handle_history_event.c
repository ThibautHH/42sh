/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_history_event
*/

#include <stdio.h>
#include <string.h>

#include "mysh/history.h"

void realloc_line(mysh_t *context, char *line, int offset)
{
    size_t len = LEN + strlen(line) + 1;

    if (len > LINESZ) {
        LINESZ = len;
        LINE = realloc(LINE, LINESZ);
        if (LINE == NULL)
            DIE;
    }
    sprintf(LINE, "%s%s", line, LINE + offset + 1);
}

static void get_offset(mysh_t *context, int *offset)
{
    for ((*offset)++; !IS_WHITESPACE(LINE[*offset]); (*offset)++);
}

bool handle_history_event(mysh_t *context)
{
    for (int i = 0; LINE[i]; i++) {
        if (LINE[i] == '!') {
            get_offset(context, &i);
            history_event(context, i);
        }
    }
    return true;
}
