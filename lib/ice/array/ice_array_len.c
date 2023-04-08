/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_array_len.c
*/

#include "ice/types.h"

size_t ice_array_len(void *array)
{
    size_t i = 0;

    if (!array)
        return 0;
    for (; ((char **)array)[i]; i++);
    return i;
}
