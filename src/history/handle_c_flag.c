/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_c_flag
*/

#include "mysh.h"

void handle_c_flag(mysh_t *context)
{
    for (list_node_t *node = context->history->tail; node; node = node->prev)
        list_remove_node(context->history, node);
}
