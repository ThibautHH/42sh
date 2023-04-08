/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_strsplit.c
*/

#include <stdlib.h>

#include "ice/string.h"

static ull_t ice_strsplit_count(char *str, char *delim, ull_t delim_len)
{
    ull_t i = 0;
    ull_t count = 0;

    for (; str[i]; i++)
        if (ice_strncmp(str + i, delim, delim_len) == 0) {
            i += delim_len - 1;
            count++;
        }
    return count + 1;
}

static ull_t ice_strsplit_len(char *str, char *delim, ull_t delim_len)
{
    ull_t i = 0;

    for (; str[i]; i++)
        if (ice_strncmp(str + i, delim, delim_len) == 0)
            return i;
    return i;
}

char **ice_strsplit(char *str, char *delim)
{
    ull_t len;
    ull_t split_count = ice_strsplit_count(str, delim, ice_strlen(delim));
    ull_t delim_len = ice_strlen(delim);
    char **tab = malloc(sizeof(char *) * (split_count + 1));

    if (!tab)
        return NULL;
    for (ull_t i = 0 ; i < split_count; i++) {
        len = ice_strsplit_len(str, delim, delim_len);
        tab[i] = malloc(sizeof(char) * (len + 1));
        if (!tab[i])
            return NULL;
        ice_strncpy(tab[i], str, len);
        str += len + delim_len;
    }
    tab[split_count] = NULL;
    return tab;
}
