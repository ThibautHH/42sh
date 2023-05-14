/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_history
*/

#include <stdio.h>
#include <string.h>

#include "mysh/history.h"

static bool history_flag(mysh_t *context)
{
    if (CMDARGS[1] && !strcmp("-c", CMDARGS[1])) {
        flag_c(context);
        return true;
    }
    return false;
}

void builtin_history(mysh_t *context)
{
    long idx_history;
    char *endptr;
    size_t c = 0;
    history_t *history;
    list_node_t *node = HISTORY->tail;

    if (history_flag(context))
        return;
    if (CMDARGS[1]) {
        idx_history = strtol(CMDARGS[1], &endptr, 10);
        if (*endptr != '\0' || idx_history < 0) {
            fprintf(stderr, "history: Badly formed number.\n");
            STATUS = 1; return;
        } c = idx_history + (idx_history == 0);
    }
    if (!c)
        node = HISTORY->head;
    else
        for (size_t i = 0; node && i < c - 1; i++)
            node = node->prev;
    for (size_t i = 0; node && (c ? i <= c : true); node = node->next, i++) {
        history = node->value;
        printf("% 6d\t%s\t%s", history->index, history->date, history->cmd);
    }
    STATUS = 0;
}
