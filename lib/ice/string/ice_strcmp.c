/*
** EPITECH PROJECT, 2022
** libice/string
** File description:
** ice_strcmp.c
*/

#include "ice/types.h"

char ice_strcmp(const char* str1, const char* str2)
{
    ull_t i = 0;

    for (; str1[i]; i++)
        if ((str1[i] < str2[i]) || str1[i] > str2[i])
            return (char)(str1[i] - str2[i]);
    return (char)(str1[i] - str2[i]);
}
