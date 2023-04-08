/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_printf_len.c
*/

#include "ice/printf/private.h"

bool ice_printf_len(buffer_t *buffer, va_list args)
{
    int *len = va_arg(args, int *);

    if (!len)
        return true;
    *len = (int)buffer->len;
    return false;
}
