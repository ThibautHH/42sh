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
 * @brief Change the current working directory
 * @param path The path to change to
 * @param env The environment
 * @return env The new environment
 */
env_t *builtin_cd(char **av, env_t *env);

/**
 * @brief Exit the shell
 * @param env The environment
 * @param av The arguments
 * @return env The new environment
 */
env_t *builtin_exit(UNUSED char **av, env_t *env);

/**
 * @brief Display the environment
 * @param env The environment
 * @return env The new environment
 */
env_t *builtin_env(UNUSED char **av, env_t *env);

/**
 * @brief Exit the shell
 * @param env The environment
 * @param av The arguments
 * @return env The new environment
 */
env_t *builtin_setenv(char **av, env_t *env);

/**
 * @brief Unset an environment variable
 * @param env The environment
 * @param buffer The buffer
 * @return env The new environment
 */
env_t *builtin_unsetenv(char **av, env_t *env);

/**
 * @brief Set an environment variable
 * @param path The path of the binary
 * @param env The environment
 * @param buffer The buffer
 * @return env The new environment
 */
bool execute_binary(char *path, char **av,  env_t *env);

/**
 * @brief Get the path of the binary
 * @param av The arguments
 * @param env The environment
 * @return char* The path of the binary
 */
env_t *load_env(char **env);

/**
 * @brief Create a new environment
 * @param env The environment
 * @return char** The new environment
 */
char **dup_env(char **env);

/**
 * @brief Fix the environment
 * @param env The environment
 * @return char** The new environment
 */
char **fix_env(char **env);

/**
 * @brief Destroy the environment
 * @param env The environment
 * @return int The status
 */
int destroy_env(env_t *env);

/**
 * @brief Get an environment variable
 * @param name The name of the variable
 * @param env The environment
 * @return char* The value of the variable
 */
char *get_env(char *name, env_t *env);

/**
 * @brief Set an environment variable
 * @param env The environment
 * @param name The name of the variable
 * @param value The value of the variable
 * @return char** The new environment
 */
char **set_env(env_t *env, char *name, char *value) ;

/**
 * @brief Unset an environment variable
 * @param env The environment
 * @param name The name of the variable
 * @return char** The new environment
 */
char **unset_env(char **env, char *name);

/**
 * @brief Display the environment
 * @param env The environment
 * @return bool True if write failed
 */
bool display_env(char **env);

/**
 * @brief Get the current working directory
 * @param env The environment
 * @return char* The current working directory
 */
void exit_env(env_t *env);

/**
 * @brief Get the current working directory
 * @param env The environment
 * @return char* The current working directory
 */
void display_error(env_t *env, const char *format, const char *str);

#endif /* !MYSH_H */
