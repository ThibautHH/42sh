/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** parser.h
*/

#ifndef INC_42SH_PARSER_H
    #define INC_42SH_PARSER_H

    #include "mysh.h"

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
 * @param env The environment
 * @param buffer The buffer
 * @return bool True if error occurred
 */
bool handle_pipe(env_t *env, char *buffer);

#endif /* !INC_42SH_PARSER_H */
