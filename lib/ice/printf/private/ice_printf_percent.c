/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_printf_percent.c
*/

#include "ice/printf/private.h"

bool ice_printf_percent(buffer_t *buffer, va_list UNUSED(args))
{
    return buffer->add(buffer, '%');
}
