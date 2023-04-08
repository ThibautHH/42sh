/*
** EPITECH PROJECT, 2022
** libice/int
** File description:
** ice_intlen.c
*/

#include "ice/types.h"

uc_t ice_intlen(ll_t nb)
{
    uc_t i = 0;

    if (nb < 0) {
        nb = -nb;
        i++;
    }
    for (; nb >= 10; i++)
        nb /= 10;
    return ++i;
}
