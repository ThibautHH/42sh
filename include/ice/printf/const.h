/*
** EPITECH PROJECT, 2023
** libice
** File description:
** const.h
*/

#ifndef LIBICE_CONST_H
    #define LIBICE_CONST_H

    #include <stddef.h>
    #include "ice/printf/private.h"

const conversion_t CONVERSION[] = {
    {'d', ice_printf_int},
    {'i', ice_printf_int},
    {'u', ice_printf_uint},
    {'o', ice_printf_octal},
    {'x', ice_printf_hexa},
    {'X', ice_printf_hexa_upper},
    {'c', ice_printf_char},
    {'s', ice_printf_str},
    {'p', ice_printf_ptr},
    {'b', ice_printf_binary},
    {'%', ice_printf_percent},
    {'n', ice_printf_len},
    {'f', ice_printf_float},
    {'\0', NULL}
};

#endif //LIBICE_CONST_H
