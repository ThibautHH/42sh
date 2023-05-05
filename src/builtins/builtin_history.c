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
#include "mysh/parser.h"
#include "ice/int.h"

static void exec_cmd(int idx_history, mysh_t *context)
{
    history_t *tmp;

    for (list_node_t *node = context->history->tail; node; node = node->prev) {
        tmp = node->value;
        if (tmp->index == idx_history)
            handle_pipe(tmp->cmd, context);
    }
}

static bool history_flag(char **av, mysh_t *context)
{
    int idx_history = 0;

    if (av[1] != NULL && ice_strcmp("-c", av[1]) == 0) {
        handle_c_flag(context);
        return false;
    }
    if (av[1] != NULL) {
        if (av[1][0] < '0' || av[1][0] > '9') {
            ice_printf("history: Badly formed number.\n");
            return false;
        }
        idx_history = ice_atoi(av[1]);
        if (idx_history > 0) {
            exec_cmd(idx_history, context);
            return false;
        }
    }
    return true;
}

bool builtin_history(char **av, mysh_t *context)
{
    history_t *tmp;

    if (!history_flag(av, context))
        return (STATUS = 0);
    for (list_node_t *node = context->history->head; node; node = node->next) {
        tmp = node->value;
        if (tmp->index < 10)
            ice_printf("    %d  %s  %s\n", tmp->index, tmp->date, tmp->cmd);
        if (tmp->index >= 10 && tmp->index < 100)
            ice_printf("   %d  %s  %s\n", tmp->index, tmp->date, tmp->cmd);
        if (tmp->index >= 100 && tmp->index < 1000)
            ice_printf("  %d  %s  %s\n", tmp->index, tmp->date, tmp->cmd);
        if (tmp->index >= 1000 && tmp->index < 10000)
            ice_printf(" %d  %s  %s\n", tmp->index, tmp->date, tmp->cmd);
    }
    return (STATUS = 0);
}
