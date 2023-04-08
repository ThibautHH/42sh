/*
** EPITECH PROJECT, 2022
** list
** File description:
** list_destroy_node.c
*/

#include <stdlib.h>

#include "list.h"

void list_destroy_node(list_t *list, void(*destroy_node)(void *))
{
    for (list_node_t *node = list->head; node; node = node->next) {
        free(node->prev);
        destroy_node(node->value);
    }
    free(list->tail);
    free(list);
}
