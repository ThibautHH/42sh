/*
** EPITECH PROJECT, 2022
** libice/string
** File description:
** ice_strlen.c
*/

#include "ice/types.h"

size_t ice_strlen(const char *str)
{
    size_t i = 0;

    if (!str)
        return 0;
    for (; str[i]; i++);
    return i;
}
