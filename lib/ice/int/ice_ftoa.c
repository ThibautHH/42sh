/*
** EPITECH PROJECT, 2023
** libice
** File description:
** ice_ftoa.c
*/

#include "ice/int.h"

void ice_ftoa(double nb, char *str, int precision)
{
    int i = 0;

    if (nb < 0) {
        str[i++] = '-';
        nb *= -1;
    }
    ice_itoa((ll_t)nb, str + i);
    for (; str[i]; i++);
    if (precision <= 0)
        return;
    str[i++] = '.';
    nb -= (double)((ll_t)nb);
    for (; precision; precision--) {
        nb *= 10;
        str[i++] = (char)((ll_t)nb % 10 + 48);
    }
    str[i] = '\0';
}
