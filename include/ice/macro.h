/*
** EPITECH PROJECT, 2023
** libice
** File description:
** macro.h
*/

#ifndef LIBICE_MACRO_H
    #define LIBICE_MACRO_H

    #include "ice/types.h"

    #define UNUSED __attribute__((unused))

    #define IS_LOWER(a) ((a) >= 'a' && (a) <= 'z')
    #define IS_UPPER(a) ((a) >= 'A' && (a) <= 'Z')

    #define ABS(a) ((a) < 0 ? -(a) : (a))
    #define MAX(a, b) ((a) > (b) ? (a) : (b))
    #define MIN(a, b) ((a) < (b) ? (a) : (b))

    #define IS_ALPHA(a) (IS_LOWER(a) || IS_UPPER(a))
    #define IS_NUM(a) ((a) >= '0' && (a) <= '9')
    #define IS_ALPHANUM(a) (IS_ALPHA(a) || IS_NUM(a))

    #define IS_ODD(a) ((a) & 1)
    #define IS_EVEN(a) (!IS_ODD(a))

#endif /* !LIBICE_MACRO_H */
