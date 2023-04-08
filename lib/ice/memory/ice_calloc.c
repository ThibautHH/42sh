/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_calloc.c
*/

#include <malloc.h>

#include "ice/types.h"

void *ice_calloc(ull_t nmemb, ull_t size)
{
    void *ptr = malloc(nmemb * size);

    if (!ptr)
        return NULL;
    for (ull_t i = 0; i < nmemb * size; i++)
        ((char *)ptr)[i] = 0;
    return ptr;
}
