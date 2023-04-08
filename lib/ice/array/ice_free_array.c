/*
** EPITECH PROJECT, 2023
** libice
** File description:
** free_array.c
*/

#include <stdlib.h>

#include "ice/types.h"

void ice_free_array(void **array)
{
    if (!array)
        return;
    for (ull_t i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
