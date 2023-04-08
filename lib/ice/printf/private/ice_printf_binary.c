/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_printf_binary.c
*/

#include "ice/int.h"
#include "ice/printf/private.h"

bool ice_printf_binary(buffer_t *buffer, va_list args)
{
    char str[100];

    if (buffer->flags & FLAG_HASH && adds_buffer(buffer, "0b"))
        return true;
    ice_btoa(va_arg(args, unsigned int), str, "01");
    return add_unsigned_width(buffer, str);
}
