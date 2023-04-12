/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** miscellaneous.h
*/

#ifndef INC_42SH_MISCELLANEOUS_H
    #define INC_42SH_MISCELLANEOUS_H

    #include "mysh.h"

/**
 * @brief Get the arguments of the command
 *
 * @param string The string
 * @return char** The arguments
 */
char **get_argument(char *buffer);

/**
 * @brief Display an error
 *
 * @param env The environment
 * @param format The format
 * @param str The string
 */
void display_error(env_t *env, const char *format, const char *str);

#endif /* !INC_42SH_MISCELLANEOUS_H */
