/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_realloc.c
*/

#include <stdlib.h>

#include "ice/types.h"

void *ice_realloc(void *ptr, ull_t size)
{
    ull_t i = 0;
    void *new_ptr = NULL;

    if (!ptr || !size)
        return NULL;
    new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;
    for (; ((char *)ptr)[i]; i++)
        ((char *)new_ptr)[i] = ((char *)ptr)[i];
    ((char *)new_ptr)[i] = '\0';
    free(ptr);
    return new_ptr;
}
