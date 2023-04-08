/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_strtrim.c
*/

#include "ice/string.h"

void ice_strtrim(char *str)
{
    ull_t len = ice_strlen(str) - 1;
    char *tmp = str;

    for (; (tmp[len] == ' ' || tmp[len] == '\t') && len > 0; len--);
    tmp[len + 1] = '\0';
    for (; (*tmp == ' ' || *tmp == '\t') && *tmp; tmp++);
    ice_strcpy(str, tmp);
}
