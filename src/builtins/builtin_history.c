/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_history
*/

#include <stdlib.h>
#include <stdio.h>

#include "mysh.h"
#include "mysh/builtins.h"
#include "mysh/history.h"
#include "mysh/commands.h"
#include "ice/int.h"

static void exec_cmd(int idx_history, mysh_t *context)
{
    history_t *tmp;

    for (list_node_t *node = HISTORY->tail; node; node = node->prev) {
        tmp = node->value;
        if (tmp->index == idx_history)
            execute_event_history_cmd(context, tmp->cmd);
    }
}

static bool history_flag(mysh_t *context)
{
    int idx_history;

    if (CMDARGS[1] != NULL && ice_strcmp("-c", CMDARGS[1]) == 0) {
        flag_c(context);
        return false;
    }
    if (CMDARGS[1] != NULL) {
        if (CMDARGS[1][0] < '0' || CMDARGS[1][0] > '9') {
            printf("history: Badly formed number.\n");
            return false;
        }
        idx_history = ice_atoi(CMDARGS[1]);
        if (idx_history > 0) {
            exec_cmd(idx_history, context);
            return false;
        }
    }
    return true;
}

void builtin_history(mysh_t *context)
{
    history_t *tmp;

    if (!history_flag(context)) {
        STATUS = 0;
        return;
    }
    for (list_node_t *node = HISTORY->head; node; node = node->next) {
        tmp = node->value;
        if (tmp->index < 10)
            printf("    %d  %s  %s", tmp->index, tmp->date, tmp->cmd);
        if (tmp->index >= 10 && tmp->index < 100)
            printf("   %d  %s  %s", tmp->index, tmp->date, tmp->cmd);
        if (tmp->index >= 100 && tmp->index < 1000)
            printf("  %d  %s  %s", tmp->index, tmp->date, tmp->cmd);
        if (tmp->index >= 1000 && tmp->index < 10000)
            printf(" %d  %s  %s", tmp->index, tmp->date, tmp->cmd);
    }
    STATUS = 0;
}
