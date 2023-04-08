/*
** EPITECH PROJECT, 2023
** list
** File description:
** list_pop_node.c
*/

#include <stdlib.h>

#include "list.h"

list_node_t *list_pop_node(list_t *list, list_node_t *node)
{
    if (node->prev != NULL)
        node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node == list->head)
        list->head = node->next;
    if (node == list->tail)
        list->tail = node->prev;
    list->size--;
    return node;
}
