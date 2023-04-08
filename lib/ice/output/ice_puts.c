/*
** EPITECH PROJECT, 2022
** libice/output
** File description:
** ice_putstr.c
*/

#include <unistd.h>

#include "ice/string.h"

ssize_t ice_puts(const char *str)
{
    return write(1, str, ice_strlen(str));
}
