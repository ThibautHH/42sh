/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_utoa.c
*/

#include "ice/string.h"

void ice_utoa(ull_t n, char *buffer)
{
    ull_t i = 0;

    for (; n; i++, n /= 10)
        buffer[i] = (char)(n % 10 + '0');
    buffer[i] = '\0';
    ice_strnrev(buffer, i - 1);
}
