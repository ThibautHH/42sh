/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_history_event
*/

#include "mysh/history.h"
#include "mysh.h"

#include <string.h>
#include <stdio.h>

void realloc_line(mysh_t *context, char *line, int offset)
{
    size_t newSize = LEN + strlen(line) + 1;
    char *rest_of_line = strdup(LINE + offset);

    if (newSize > LINESZ) {
        LINESZ = newSize;
        LINE = realloc(LINE, LINESZ);
        if (LINE == NULL)
            DIE;
    }
    strcpy(LINE + offset, line);
    strcat(LINE + offset + strlen(line), rest_of_line);
    free(rest_of_line);
}

_Bool handle_history_event(mysh_t *context)
{
    for (int i = 0; LINE[i]; i++) {
        if (LINE[i] == '!')
            history_event(context, i);
    }
    return true;
}
