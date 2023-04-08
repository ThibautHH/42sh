/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_printf_octal.c
*/

#include "ice/int.h"
#include "ice/printf/private.h"

bool ice_printf_octal(buffer_t *buffer, va_list args)
{
    ui_t nb = va_arg(args, unsigned int);
    char str[100];

    if ((buffer->flags & FLAG_HASH) && (nb != 0) && adds_buffer(buffer, "0"))
        return true;
    ice_btoa(nb, str, "01234567");
    return add_unsigned_width(buffer, str);
}
