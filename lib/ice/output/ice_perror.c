/*
** EPITECH PROJECT, 2022
** libice/output
** File description:
** ice_perror.c
*/

#include <unistd.h>

#include "ice/string.h"

ull_t ice_perror(const char *str)
{
    return write(2, str, ice_strlen(str));
}
