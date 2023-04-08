/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_strstr.c
*/

#include <stddef.h>

#include "ice/types.h"

char *ice_strstr(const char *haystack, const char *needle)
{
    for (ull_t i = 0, j = 0 ; haystack[i] ; i++) {
        if (haystack[i] == needle[j]) {
            j++;
        } else
            j = 0;
        if (!needle[j])
            return ((char *) haystack + i - j + 1);
    }
    return NULL;
}
