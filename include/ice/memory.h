/*
** EPITECH PROJECT, 2023
** libice
** File description:
** memory.h
*/

#ifndef LIBICE_MEMORY_H
    #define LIBICE_MEMORY_H

    #include "ice/types.h"

/**
 * @brief Allocate n bytes of memory
 * @param size The size of the memory to allocate
 * @return A pointer to the allocated memory
 * @note The allocated memory is not initialized
 * @note If size is 0, a NULL pointer is returned
 */
void *ice_realloc(void *ptr, ull_t size);

/**
 * @brief Allocate n bytes of memory
 * @param nmemb The number of elements
 * @param size The size of each element
 * @return A pointer to the allocated memory
 */
void *ice_calloc(ull_t nmemb, ull_t size);

/**
 * @brief Copy n bytes from src to dest
 * @param dest The destination
 * @param src The source
 * @param n The number of bytes to copy
 * @return The destination
 */
void *ice_memcpy(void *dest, const void *src, ull_t n);

/**
 * @brief Set n bytes of s to c
 * @param s The string
 * @param c The character
 * @param n The number of bytes to set
 * @return The string
 */
void *ice_memset(void *s, int c, ull_t n);

/**
 * @brief Find the first occurrence of c in s
 * @param s The string
 * @param c The character
 * @param n The number of bytes to search
 * @return The first occurrence of c in s
 */
void *ice_memchr(const void *s, int c, ull_t n);

/**
 * @brief Compare n bytes of s1 and s2
 * @param s1 The first string
 * @param s2 The second string
 * @param n The number of bytes to compare
 * @return 0 if s1 and s2 are equal,
 * @return a negative value if s1 is less than s2,
 * @return a positive value if s1 is greater than s2
 */
int ice_memcmp(const void *s1, const void *s2, ull_t n);

/**
 * @brief Copy n bytes from src to dest
 * @param dest The destination
 * @param src The source
 * @param n The number of bytes to copy
 * @return The destination
 */
void *ice_memmove(void *dest, const void *src, ull_t n);

#endif /* !LIBICE_MEMORY_H */
