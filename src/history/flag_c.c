/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** flag_c
*/

#include "mysh.h"

void flag_c(mysh_t *context)
{
    for (list_node_t *node = context->history->tail; node; node = node->prev)
        list_remove_node(context->history, node);
}
