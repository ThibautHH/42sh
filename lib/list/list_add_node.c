/*
** EPITECH PROJECT, 2022
** list
** File description:
** list_add_node.c
*/

#include <stdlib.h>

#include "list.h"

bool list_add_node(list_t *list, list_node_t *node)
{
    if (list == NULL || node == NULL)
        return false;
    list->size++;
    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
        return true;
    }
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
    return true;
}
