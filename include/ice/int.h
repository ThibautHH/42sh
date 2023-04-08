/*
** EPITECH PROJECT, 2022
** libice
** File description:
** ice/int.h
*/

#ifndef ICE_INT_H
    #define ICE_INT_H

    #include "ice/types.h"

/**
 * @brief Get the len of a int.
 * @param nb that will be get.
 * @return The len of the int.
 */
uc_t ice_intlen(ll_t nb);

/**
 * @brief Convert a int to a string.
 * @param nb that will be converted.
 * @param buffer that will be filled.
 * @return The len of the string.
 */
void ice_itoa(ll_t nb, char *buffer);

/**
 * @brief Convert a unsigned int to a string.
 * @param nb that will be converted.
 * @param buffer that will be filled.
 * @return The len of the string.
 */
void ice_utoa(ull_t n, char *buffer);

/**
 * @brief Convert a int to a string with a base.
 * @param nb that will be converted.
 * @param buffer that will be filled.
 * @param base that will be used.
 */
void ice_btoa(ull_t nb, char *buffer, char *base);

/**
 * @brief Convert a float to a string.
 * @param nb that will be converted.
 * @param str that will be filled.
 * @param precision of the float.
 */
void ice_ftoa(double nb, char *str, int precision);

/**
 * @brief Convert a string to a int.
 * @param str that will be converted.
 * @return The int.
 */
ll_t ice_atoi(const char *str);

/**
 * @brief Convert a string to a int.
 * @param str that will be converted.
 * @param endptr next character in str after the numerical value.
 * @return The int.
 */
ll_t ice_strtol(const char *str, char **endptr);

#endif /* !ICE_INT_H */
