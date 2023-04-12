/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** execution.h
*/

#ifndef INC_42SH_EXECUTION_H
    #define INC_42SH_EXECUTION_H

    #include "mysh.h"

/**
 * @brief Search for a function
 * @param av The arguments
 * @param env The environment
 * @return bool True if error occurred
 */
bool search_function(char **av, env_t *env);

/**
 * @brief Set an environment variable
 * @param path The path of the binary
 * @param env The environment
 * @param buffer The buffer
 * @return env The new environment
 */
bool execute_binary(char *path, char **av,  env_t *env);

#endif /* !INC_42SH_EXECUTION_H */
