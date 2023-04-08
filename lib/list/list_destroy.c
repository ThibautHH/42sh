/*
** EPITECH PROJECT, 2022
** list
** File description:
** list_destroy.c
*/

#include <stdlib.h>

#include "list.h"

void list_destroy(list_t *list)
{
    for (list_node_t *node = list->head; node; node = node->next)
        free(node->prev);
    free(list->tail);
    free(list);
}
