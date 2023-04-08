/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_sprintf.c
*/

#include <limits.h>

#include "ice/printf/private.h"

ssize_t ice_sprintf(char *str, const char *format, ...)
{
    va_list args;
    buffer_t buffer = {0};

    if (!str || !format)
        return -1;
    buffer.str = str;
    buffer.left = LLONG_MAX;
    buffer.add = addn_buffer;
    va_start(args, format);
    if (handle_format(&buffer, format, args))
        return -1;
    va_end(args);
    buffer.str[buffer.len] = '\0';
    return buffer.len;
}
