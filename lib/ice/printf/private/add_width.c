/*
** EPITECH PROJECT, 2023
** libice
** File description:
** add_width.c
*/

#include "ice/string.h"
#include "ice/printf/private.h"

bool add_width_len(buffer_t *buffer, ull_t len, char c)
{
    for (ull_t i = len; i < buffer->width; i++)
        if (buffer->add(buffer, c))
            return true;
    return false;
}

static bool number_add_width(buffer_t *buffer, char *str, ull_t len)
{
    char c = (buffer->flags & FLAG_ZERO) ? '0' : ' ';
    ull_t width_len;

    width_len = buffer->prec != (ull_t)-1 ? MAX(len, buffer->prec) : len;
    if (!(buffer->flags & FLAG_MINUS) && add_width_len(buffer, width_len, c))
        return true;
    if (buffer->prec != (ull_t)-1) {
        len = MAX(len, buffer->prec);
        if (add_width_len(buffer, buffer->prec - len, '0'))
            return true;
    }
    return (adds_buffer(buffer, str))
        || (buffer->flags & FLAG_MINUS
        && add_width_len(buffer, width_len, ' '));
}

bool add_unsigned_width(buffer_t *buffer, char *str)
{
    ull_t len = ice_strlen(str);

    if (buffer->flags & FLAG_HASH)
        len += 2;
    return number_add_width(buffer, str, len);
}

bool add_signed_width(buffer_t *buffer, char *str)
{
    ull_t len = ice_strlen(str);

    if (buffer->flags & FLAG_SPACE || buffer->flags & FLAG_PLUS)
        len++;
    return number_add_width(buffer, str, len);
}

bool add_width(buffer_t *buffer, char *str)
{
    ull_t len = ice_strlen(str);

    return (!(buffer->flags & FLAG_MINUS) && add_width_len(buffer, len, ' '))
        || (adds_buffer(buffer, str))
        || (buffer->flags & FLAG_MINUS && add_width_len(buffer, len, ' '));
}
