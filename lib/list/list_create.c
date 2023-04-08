/*
** EPITECH PROJECT, 2022
** list
** File description:
** list_create.c
*/

#include <stdlib.h>

#include "list.h"

list_t *list_create(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}
