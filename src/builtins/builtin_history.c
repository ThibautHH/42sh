/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_history
*/

#include <stdio.h>
#include <string.h>

#include "mysh/history.h"

static void exec_cmd(int idx_history, mysh_t *context)
{
    for (list_node_t *node = HISTORY->tail; node; node = node->prev) {
        if (((history_t *)node->value)->index != idx_history)
            continue;
        execute_event_history_cmd(context, ((history_t *)node->value)->cmd);
    }
}

static bool history_flag(mysh_t *context)
{
    int idx_history;

    if (CMDARGS[1] && !strcmp("-c", CMDARGS[1])) {
        flag_c(context);
        return false;
    }
    if (CMDARGS[1]) {
        if (CMDARGS[1][0] < '0' || CMDARGS[1][0] > '9') {
            printf("history: Badly formed number.\n");
            return false;
        }
        idx_history = strtol(CMDARGS[1], NULL, 10);
        if (idx_history > 0) {
            exec_cmd(idx_history, context);
            return false;
        }
    }
    return true;
}

void builtin_history(mysh_t *context)
{
    history_t *history;

    STATUS = 0;
    if (!history_flag(context))
        return;
    for (list_node_t *node = HISTORY->head; node; node = node->next) {
        history = node->value;
        printf("%5i  %s   %s", history->index, history->date, history->cmd);
    }
}
