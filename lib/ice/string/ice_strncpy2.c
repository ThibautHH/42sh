/*
** EPITECH PROJECT, 2023
** libmy
** File description:
** String copying functions
*/

#include <stddef.h>

#include "ice/string.h"

char *ice_strncpy2(char *dest, const char *src, size_t n)
{
    if (!dest || !src)
        return NULL;
    size_t i = 0;
    size_t src_len = ice_strlen(src);
    size_t src_end = src_len < n ? src_len : n;
    for (; i < src_end; i++)
        dest[i] = src[i];
    if (i >= n)
        return dest;
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}
