/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** execution.h
*/

#ifndef INC_42SH_EXECUTION_H
    #define INC_42SH_EXECUTION_H

    #include "mysh.h"

/**
 * @brief Search for a function
 *
 * @param av The arguments
 * @param env The environment
 * @return bool True if error occurred
 */
bool search_function(char **av, mysh_t *context);

/**
 * @brief Execute a binary
 *
 * @param path The path of the binary
 * @param av The arguments
 * @param env The environment
 */
bool execute_binary(char *path, char **av,  mysh_t *context);

#endif /* !INC_42SH_EXECUTION_H */
