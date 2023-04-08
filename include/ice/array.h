/*
** EPITECH PROJECT, 2023
** libice
** File description:
** array.h
*/

#ifndef LIBICE_ARRAY_H
    #define LIBICE_ARRAY_H

    #include "ice/types.h"

/**
 * @brief Returns the length of an array.
 * @param array The array to get the length of.
 * @return The length of the array.
 */
size_t ice_array_len(void *array);

/**
 * @brief Frees an array.
 * @param array The array to free.
 */
void ice_free_array(void **array);

#endif /* !LIBICE_ARRAY_H */
