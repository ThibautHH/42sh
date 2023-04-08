/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_sprintf.c
*/

#include <malloc.h>

#include "ice/printf/private.h"

ssize_t ice_asprintf(char **restrict str, const char *restrict format, ...)
{
    va_list args;
    buffer_t buffer = {0};

    if (str == NULL || format == NULL) {
        *str = NULL;
        return -1;
    }
    buffer.str = malloc(sizeof(char) * 1024);
    buffer.left = 1024;
    buffer.add = add_buffer;
    va_start(args, format);
    if (handle_format(&buffer, format, args) || buffer.add(&buffer, '\0'))
        return -1;
    va_end(args);
    *str = buffer.len != -1 ? buffer.str : NULL;
    return buffer.len - 1;
}
