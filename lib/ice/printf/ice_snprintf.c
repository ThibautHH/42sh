/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_snprintf.c
*/

#include <stdlib.h>

#include "ice/printf/private.h"

ssize_t ice_snprintf(char *str, ull_t n, const char *format, ...)
{
    va_list args;
    buffer_t buffer = {0};

    if (!str || !format)
        return -1;
    buffer.str = str;
    buffer.left = (ssize_t)n;
    buffer.add = addn_buffer;
    va_start(args, format);
    if (handle_format(&buffer, format, args))
        return -1;
    va_end(args);
    buffer.str[buffer.len] = '\0';
    return buffer.len;
}
