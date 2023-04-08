/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_dprintf.c
*/

#include <malloc.h>
#include <unistd.h>

#include "ice/printf/private.h"

ssize_t ice_dprintf(int fd, const char *restrict format, ...)
{
    va_list args;
    buffer_t buffer = {0};
    ssize_t len;

    if (!format)
        return -1;
    buffer.str = malloc(sizeof(char) * 1024);
    buffer.left = 1024;
    buffer.add = add_buffer;
    va_start(args, format);
    if (handle_format(&buffer, format, args))
        return -1;
    va_end(args);
    len = write(fd, buffer.str, buffer.len);
    free(buffer.str);
    return len;
}
