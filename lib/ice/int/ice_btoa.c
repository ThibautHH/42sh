/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_btoa.c
*/

#include "ice/string.h"

void ice_btoa(ull_t nb, char *buffer, char *base)
{
    ull_t i = 0;
    ull_t base_len = ice_strlen(base);

    for (; nb >= base_len; i++) {
        buffer[i] = base[nb % base_len];
        nb /= base_len;
    }
    buffer[i] = base[nb];
    buffer[i + 1] = '\0';
    ice_strrev(buffer);
}
