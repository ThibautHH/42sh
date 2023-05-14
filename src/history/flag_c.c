/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** flag_c
*/

#include "mysh/history.h"

void flag_c(mysh_t *context)
{
    for (list_node_t *node = HISTORY->tail, *tmp;
        node && ((tmp = node->prev), 1); node = tmp)
        free_history((history_t *)(list_remove_node(HISTORY, node)));
}
