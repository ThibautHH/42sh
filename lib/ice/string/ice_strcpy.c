/*
** EPITECH PROJECT, 2022
** libice/string
** File description:
** ice_strcpy.c
*/

#include "ice/types.h"

void ice_strcpy(char *dest, const char *src)
{
    ull_t i = 0;

    for (; src[i]; i++)
        dest[i] = src[i];
    dest[i] = '\0';
}
