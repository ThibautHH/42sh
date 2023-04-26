/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_history
*/

#include <stdlib.h>

#include "mysh.h"
#include "mysh/history.h"

bool builtin_history(UNUSED char **av, mysh_t *context)
{
    history_t *tmp;

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
