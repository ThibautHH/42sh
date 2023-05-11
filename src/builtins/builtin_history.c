/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_history
*/

#include <stdlib.h>

#include "mysh.h"
#include "mysh/builtins.h"
#include "mysh/history.h"
#include "ice/int.h"
#include "ice/printf.h"

static bool history_flag(mysh_t *context)
{
    if (CMDARGS[1] != NULL && ice_strcmp("-c", CMDARGS[1]) == 0) {
        flag_c(context);
        return false;
    }
    if (CMDARGS[1] != NULL) {
        if (CMDARGS[1][0] < '0' || CMDARGS[1][0] > '9') {
            ice_printf("history: Badly formed number.\n");
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
            ice_printf("    %d  %s  %s", tmp->index, tmp->date, tmp->cmd);
        if (tmp->index >= 10 && tmp->index < 100)
            ice_printf("   %d  %s  %s", tmp->index, tmp->date, tmp->cmd);
        if (tmp->index >= 100 && tmp->index < 1000)
            ice_printf("  %d  %s  %s", tmp->index, tmp->date, tmp->cmd);
        if (tmp->index >= 1000 && tmp->index < 10000)
            ice_printf(" %d  %s  %s", tmp->index, tmp->date, tmp->cmd);
    }

    STATUS = 0;
}
