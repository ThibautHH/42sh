/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** redirection.h
*/

#ifndef MYSH_REDIRECTION_H
    #define MYSH_REDIRECTION_H

    #include "mysh.h"

//
// Structs
//

typedef struct redir_s {
    enum {ADD, APPEND} output;
    enum {READ, INPUT} input;
    int fd_out[2];
    char *file_out;
    int fd_in[2];
    char *file_in;
} redir_t;


//
// Set redirection
//

/**
 * @brief Set the redirection
 * @param redir The redirection
 * @param str The string
 * @param env The environment
 * @return bool False if error occurred
 */
bool set_redirection(redir_t *redir, char *str, env_t *env);

/**
 * @brief Set the output redirection
 * @param redir The redirection
 * @param str The string
 * @param env The environment
 * @return bool False if error occurred
 */
bool set_redirection_output(redir_t *redir, char *str, env_t *env);

/**
 * @brief Set the input redirection
 * @param redir The redirection
 * @param str The string
 * @param env The environment
 * @return bool False if error occurred
 */
bool set_redirection_input(redir_t *redir, char *str, env_t *env);

//
// Unset redirection
//

/**
 * @brief Unset the redirection
 * @param redir The redirection
 * @return bool False if error occurred
 */
bool unset_redirection(redir_t *redir);

/**
 * @brief Unset the output redirection
 * @param redir The redirection
 * @return bool False if error occurred
 */
bool unset_redirection_output(redir_t *redir);

/**
 * @brief Unset the input redirection
 * @param redir The redirection
 * @return bool False if error occurred
 */
bool unset_redirection_input(redir_t *redir);

//
// Extract redirection
//

/**
 * @brief Extract the output redirection
 * @param redir The redirection
 * @param str The string
 * @param start The start of the string
 * @param end The end of the string
 */
bool extract_output(redir_t *redir, char *str, char *start);

/**
 * @brief Extract the input redirection
 * @param redir The redirection
 * @param str The string
 * @param start The start of the string
 * @param end The end of the string
 */
bool extract_input(redir_t *redir, char *str, char *start);

#endif /* !MYSH_REDIRECTION_H */
