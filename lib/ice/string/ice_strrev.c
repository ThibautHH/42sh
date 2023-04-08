/*
** EPITECH PROJECT, 2023
** libice/string
** File description:
** ice_strrev.c
*/

#include "ice/string.h"

void ice_strrev(char *str)
{
    ssize_t i = 0;
    ssize_t j = (ssize_t)ice_strlen(str) - 1;

    if (!str || j == -1)
        return;
    for (; i < j ; i++, j--)
        ice_strswap(str, i, j);
}
