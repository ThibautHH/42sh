/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_printf_int.c
*/

#include "ice/int.h"
#include "ice/printf/private.h"

bool ice_printf_int(buffer_t *buffer, va_list args)
{
    int nb = va_arg(args, int);
    char str[12];

    if ((nb >= 0)
        && ((buffer->flags & FLAG_SPACE && buffer->add(buffer, ' '))
        || (buffer->flags & FLAG_PLUS && buffer->add(buffer, '+'))))
        return true;
    ice_itoa(nb, str);
    return add_signed_width(buffer, str);
}
