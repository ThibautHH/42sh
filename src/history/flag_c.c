/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** flag_c
*/

#include "mysh.h"
#include "mysh/history.h"
#include "list.h"

void flag_c(mysh_t *context)
{
    for (list_node_t *node = HISTORY->tail; node; node = node->prev)
        list_remove_node(HISTORY, node);
}
