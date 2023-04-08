/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_printf_ptr.c
*/

#include "ice/int.h"
#include "ice/printf/private.h"

bool ice_printf_ptr(buffer_t *buffer, va_list args)
{
    char str[12];

    if (adds_buffer(buffer, "0x"))
        return true;
    ice_btoa(va_arg(args, unsigned long int), str, "0123456789abcdef");
    return add_width(buffer, str);
}
