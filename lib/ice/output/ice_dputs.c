/*
** EPITECH PROJECT, 2022
** libice/output
** File description:
** ice_dputs.c
*/

#include <unistd.h>

#include "ice/string.h"

ssize_t ice_dputs(int fd, const char *str)
{
    return write(fd, str, ice_strlen(str));
}
