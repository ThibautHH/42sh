/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_printf_str.c
*/

#include <stdlib.h>

#include "ice/macro.h"
#include "ice/string.h"
#include "ice/printf/private.h"

bool ice_printf_str(buffer_t *buffer, va_list args)
{
    char *str = va_arg(args, char *);

    if (!str) {
        str = "(null)";
        buffer->prec = -1;
    }
    if (buffer->prec != (ull_t)-1)
        str = ice_strndup(str, buffer->prec);
    if (!str || add_width(buffer, str))
        return true;
    if (buffer->prec != (ull_t)-1)
        free(str);
    return false;
}
