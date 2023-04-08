/*
** EPITECH PROJECT, 2022
** list
** File description:
** list_remove_node.c
*/

#include <stdlib.h>

#include "list.h"

void *list_remove_node(list_t *list, list_node_t *node)
{
    void *value;

    if ((list == NULL) || (node == NULL))
        return NULL;
    list_pop_node(list, node);
    value = node->value;
    free(node);
    return value;
}
