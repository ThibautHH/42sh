/*
** EPITECH PROJECT, 2023
** libice/string
** File description:
** ice_strswap.c
*/

#include "ice/types.h"

void ice_strswap(char *str, ull_t a, ull_t b)
{
    char tmp = str[a];

    str[a] = str[b];
    str[b] = tmp;
}
