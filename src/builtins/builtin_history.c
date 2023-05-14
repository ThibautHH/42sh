/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_history
*/

#include <stdio.h>
#include <string.h>

#include "mysh/history.h"

static bool clear_history(mysh_t *context)
{
    if (!CMDARGS[1] || strcmp("-c", CMDARGS[1]))
        return false;
    for (list_node_t *node = HISTORY->tail, *tmp;
        node && ((tmp = node->prev), 1); node = tmp)
        free_history((history_t *)(list_remove_node(HISTORY, node)));
    return true;
}

static void print_nodes(mysh_t *context, size_t c)
{
    history_t *history;
    list_node_t *node = HISTORY->tail;

    if (!c)
        node = HISTORY->head;
    else
        for (size_t i = 0; node && i < c - 1; i++)
            node = node->prev;
    for (size_t i = 0; node && (c ? i <= c : true); node = node->next, i++) {
        history = node->value;
        PRINT("% 6d\t%s\t%s", history->index, history->date, history->cmd);
    }
}

void builtin_history(mysh_t *context)
{
    long idx_history;
    char *endptr;
    size_t c = 0;

    if (clear_history(context))
        return;
    if (CMDARGS[1]) {
        idx_history = strtol(CMDARGS[1], &endptr, 10);
        if (*endptr || idx_history < 0) {
            ERRPRINT("history: Badly formed number.\n");
            STATUS = 1;
            return;
        }
        c = (idx_history == 0) ? 1 : idx_history;
    }
    print_nodes(context, c);
    STATUS = 0;
}
