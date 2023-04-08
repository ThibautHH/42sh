/*
** EPITECH PROJECT, 2023
** libice
** File description:
** printf.h
*/

#ifndef LIBICE_PRINTF_H
    #define LIBICE_PRINTF_H

    #include "ice/types.h"

/**
 * @brief Print in the stdout.
 * @param format that will be printed.
 * @param ... that will be printed.
 * @return The len of the str.
 */
ssize_t ice_printf(const char *restrict format, ...);

/**
 * @brief Print in the fd.
 * @param fd that will be printed.
 * @param format that will be printed.
 * @param ... that will be printed.
 * @return The len of the str.
 */
ssize_t ice_dprintf(int fd, const char *restrict format, ...);

/**
 * @brief Print in the str.
 * @param str that will be printed.
 * @param format that will be printed.
 * @param ... that will be printed.
 * @return The len of the str.
 */
ssize_t ice_sprintf(char *str, const char *format, ...);

/**
 * @brief Print in the str.
 * @param str that will be printed.
 * @param n that will be printed.
 * @param format that will be printed.
 * @param ... that will be printed.
 * @return The len of the str.
 */
ssize_t ice_snprintf(char *str, ull_t n, const char *format, ...);

/**
 * @brief Print in the str.
 * @param str that will be printed.
 * @param format that will be printed.
 * @param ... that will be printed.
 * @return The len of the str.
 */
ssize_t ice_asprintf(char **restrict str, const char *restrict format, ...);

#endif /* !LIBICE_PRINTF_H */
