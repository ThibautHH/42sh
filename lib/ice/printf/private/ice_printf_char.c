/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_printf_char.c
*/

#include "ice/printf/private.h"

bool ice_printf_char(buffer_t *buffer, va_list args)
{
    char c = va_arg(args, int);

    return add_width_len(buffer, 1, ' ') || buffer->add(buffer, c);
}
