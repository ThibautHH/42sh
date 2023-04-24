/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_realloc.c
*/

#include <stdlib.h>

#include "ice/types.h"
#include "ice/memory.h"

void *ice_realloc2(void *ptr, size_t originalLength, size_t newLength)
{
    if (!newLength) {
        free(ptr);
        return NULL;
    }
    if (!ptr)
        return malloc(newLength);
    if (newLength <= originalLength)
        return ptr;
    void *ptrNew = malloc(newLength);
    if (ptrNew)
        ice_memcpy(ptrNew, ptr, originalLength);
    else
        return NULL;
    free(ptr);
    return ptrNew;
}
