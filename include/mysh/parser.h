/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** parser.h
*/

#ifndef INC_42SH_PARSER_H
    #define INC_42SH_PARSER_H

    #include "mysh.h"

//
// Handle
//

/**
 * @brief Handle the input of the user
 *
 * @param env The environment
 * @return bool True if error occurred
 */
bool handle_input(env_t *env);

/**
 * @brief Handle the sequence of commands
 *
 * @param buffer The buffer
 * @param env The environment
 * @return bool True if error occurred
 */
bool handle_sequence(char *buffer, env_t *env);

/**
 * @brief Handle the pipe of commands
 *
 * @param buffer The buffer
 * @param env The environment
 * @return bool True if error occurred
 */
bool handle_pipe(char *buffer, env_t *env);

#endif /* !INC_42SH_PARSER_H */
