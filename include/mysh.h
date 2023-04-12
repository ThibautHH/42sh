/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** mysh.h
*/

#ifndef MYSH_H
    #define MYSH_H

    #include <stdbool.h>

    #include "ice/macro.h"

    #define IS_END(x) ((x == '\0') || (x == '\n'))
    #define IS_SPACE(x) ((x == ' ') || (x == '\t'))

typedef struct env_s {
    char **env;
    int status;
    bool exit;
} env_t;

/**
 * @brief Get the arguments of the command
 * @param string The string
 * @return char** The arguments
 * @note The string must be null terminated
 */
char **get_argument(char *buffer);

/**
 * @brief Get the current working directory
 * @param env The environment
 * @return char* The current working directory
 */
void display_error(env_t *env, const char *format, const char *str);

#endif /* !MYSH_H */
