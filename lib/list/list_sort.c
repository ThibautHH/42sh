/*
** EPITECH PROJECT, 2022
** list
** File description:
** list_sort.c
*/

#include "list.h"

static void swap_node(list_node_t *node1, list_node_t *node2)
{
    void *tmp = node1->value;

    node1->value = node2->value;
    node2->value = tmp;
}

static void list_revsort(list_node_t *node, ull_t (*cmp)(void *, void *))
{
    while ((node->prev) && (cmp(node->prev->value, node->value) > 0)) {
        swap_node(node->prev, node);
        node = node->prev;
    }
}

void list_sort(list_t *list, ull_t (*cmp)(void *, void *))
{
    if (list->size == 0)
        return;
    for (list_node_t *node = list->head->next ; node ; node = node->next) {
        if (cmp(node->prev->value, node->value) > 0) {
            swap_node(node->prev, node);
            list_revsort(node->prev, cmp);
        }
    }
}
