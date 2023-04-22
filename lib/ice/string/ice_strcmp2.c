/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** String comparison functions
*/

#include "ice/string.h"

int ice_strcmp2(const char *a, const char *b)
{
    char result = 0;
    size_t len_a = ice_strlen(a) + 1;
    size_t len_b = ice_strlen(b) + 1;
    size_t max = len_a < len_b ? len_a : len_b;
    for (size_t i = 0; i < max; i++) {
        result = a[i] - b[i];
        if (result)
            return result;
    }
    return result;
}

int ice_strncmp2(const char *a, const char *b, size_t n)
{
    char result = 0;
    size_t len_a = ice_strlen(a) + 1;
    size_t len_b = ice_strlen(b) + 1;
    size_t max = len_a < len_b ? len_a : len_b;
    max = max < n ? max : n;
    for (size_t i = 0; i < max; i++) {
        result = a[i] - b[i];
        if (result)
            return result;
    }
    return result;
}
