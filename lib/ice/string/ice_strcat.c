/*
** EPITECH PROJECT, 2022
** libice/string
** File description:
** ice_strcat.c
*/

#include "ice/macro.h"
#include "ice/string.h"

void ice_strcat(char *dest, const char *src)
{
    ice_strcpy((dest + ice_strlen(dest)), src);
}
