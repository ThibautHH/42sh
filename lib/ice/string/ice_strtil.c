/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_strtil.c
*/

#include <stddef.h>

size_t ice_strtil(const char *str, char c)
{
    register size_t offset = 0;
    while (str[offset] && str[offset] != c)
        offset++;
    return offset;
}
