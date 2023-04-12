/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** mysh.h
*/

#ifndef MYSH_H
    #define MYSH_H

    #include <stdarg.h>
    #include <unistd.h>
    #include <stdbool.h>

    #include "ice/types.h"
    #include "ice/macro.h"

    #define IS_END(x) ((x == '\0') || (x == '\n'))
    #define IS_SPACE(x) ((x == ' ') || (x == '\t'))

typedef struct env_s {
    char **env;
    int status;
    bool exit;
} env_t;

/**
 * @brief Search for a function
 * @param av The arguments
 * @param env The environment
 * @return bool True if error occurred
 */
bool search_function(char **av, env_t *env);

/**
 * @brief Get the arguments of the command
 * @param string The string
 * @return char** The arguments
 * @note The string must be null terminated
 */
char **get_argument(char *buffer);

/**
 * @brief Set an environment variable
 * @param path The path of the binary
 * @param env The environment
 * @param buffer The buffer
 * @return env The new environment
 */
bool execute_binary(char *path, char **av,  env_t *env);

/**
 * @brief Get the current working directory
 * @param env The environment
 * @return char* The current working directory
 */
void display_error(env_t *env, const char *format, const char *str);

/**
 * @brief Get the current working directory
 * @param env The environment
 * @return char* The current working directory
 */
bool handle_input(env_t *env);

/**
 * @brief Get the current working directory
 * @param env The environment
 * @return char* The current working directory
 */
bool handle_sequence(char *buffer, env_t *env);

/**
 * @brief Get the current working directory
 * @param env The environment
 * @return char* The current working directory
 */
bool handle_pipe(env_t *env, char *buffer);

#endif /* !MYSH_H */
