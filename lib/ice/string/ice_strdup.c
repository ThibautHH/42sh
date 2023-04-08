/*
** EPITECH PROJECT, 2023
** libice/string
** File description:
** ice_strdup.c
*/

#include <stdlib.h>

#include "ice/macro.h"
#include "ice/string.h"

char *ice_strdup(const char *str)
{
    char *new = malloc(sizeof(char) * (ice_strlen(str) + 1));

    if (!new || !str)
        return NULL;
    ice_strcpy(new, str);
    return new;
}
