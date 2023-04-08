/*
** EPITECH PROJECT, 2023
** libice
** File description:
** printf.h
*/

#ifndef LIBICE_PRIVATE_H
    #define LIBICE_PRIVATE_H

    #include <stdarg.h>
    #include <stdbool.h>

    #include "ice/macro.h"
    #include "ice/printf/struct.h"

bool handle_format(buffer_t *buffer, const char *format, va_list args);

void get_flags(buffer_t *buffer, const char *format, ull_t *i);

void get_width(buffer_t *buffer, const char *format, ull_t *i, va_list args);

void get_precision(buffer_t *buffer, const char *format,
    ull_t *i, va_list args);

bool get_conversion(buffer_t *buffer, char c, va_list args);

bool add_buffer(buffer_t *buffer, char c);

bool addn_buffer(buffer_t *buffer, char c);

bool adds_buffer(buffer_t *buffer, char *str);

bool add_width(buffer_t *buffer, char *str);

bool add_width_len(buffer_t *buffer, ull_t len, char c);

bool add_signed_width(buffer_t *buffer, char *str);

bool add_unsigned_width(buffer_t *buffer, char *str);

bool ice_printf_char(buffer_t *buffer, va_list args);

bool ice_printf_str(buffer_t *buffer, va_list args);

bool ice_printf_percent(buffer_t *buffer, va_list UNUSED(args));

bool ice_printf_int(buffer_t *buffer, va_list args);

bool ice_printf_uint(buffer_t *buffer, va_list args);

bool ice_printf_binary(buffer_t *buffer, va_list args);

bool ice_printf_octal(buffer_t *buffer, va_list args);

bool ice_printf_hexa(buffer_t *buffer, va_list args);

bool ice_printf_hexa_upper(buffer_t *buffer, va_list args);

bool ice_printf_ptr(buffer_t *buffer, va_list args);

bool ice_printf_len(buffer_t *buffer, va_list args);

bool ice_printf_float(buffer_t *buffer, va_list args);

#endif /* !LIBICE_PRIVATE_H */
