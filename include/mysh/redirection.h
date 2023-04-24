/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** redirection.h
*/

#ifndef MYSH_REDIRECTION_H
    #define MYSH_REDIRECTION_H

    #include <stdbool.h>

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
} redirs_t;


typedef struct mysh_s mysh_t;

//
// Set redirection
//

/**
 * @brief Set the redirection
 *
 * @param redir The redirection
 * @param str The string
 * @param env The environment
 * @return bool True if error occurred
 */
bool set_redirection(redirs_t *redir, char *str, mysh_t *context);

/**
 * @brief Set the output redirection
 *
 * @param redirs The redirection
 * @param str The string
 * @param env The environment
 * @return bool False if error occurred
 */
bool set_redirection_output(redirs_t *redirs, char *str, mysh_t *context);

/**
 * @brief Set the input redirection
 *
 * @param redirs The redirection
 * @param str The string
 * @param env The environment
 * @return bool False if error occurred
 */
bool set_redirection_input(redirs_t *redirs, char *str, mysh_t *context);

//
// Unset redirection
//

/**
 * @brief Unset the redirection
 *
 * @param redir The redirection
 * @return bool True if error occurred
 */
bool unset_redirection(redirs_t *redir);

/**
 * @brief Unset the output redirection
 *
 * @param redir The redirection
 * @return bool False if error occurred
 */
bool unset_redirection_output(redirs_t *redir);

/**
 * @brief Unset the input redirection
 *
 * @param redir The redirection
 * @return bool False if error occurred
 */
bool unset_redirection_input(redirs_t *redir);

//
// Extract redirection
//

/**
 * @brief Extract the output redirection
 *
 * @param redir The redirection
 * @param str The string
 * @param start The start of the string
 */
bool extract_output(redirs_t *redir, char *str, char *start);

/**
 * @brief Extract the input redirection
 *
 * @param redirs The redirection
 * @param str The string
 * @param start The start of the string
 */
bool extract_input(redirs_t *redirs, char *str, char *start);

#endif /* !MYSH_REDIRECTION_H */
