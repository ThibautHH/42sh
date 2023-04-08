/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_strchr.c
*/

#include <stddef.h>

#include "ice/types.h"

char *ice_strchr(const char *str, char c)
{
    for (ull_t i = 0; str[i]; i++)
        if (str[i] == c)
            return ((char *) str + i);
    return NULL;
}
