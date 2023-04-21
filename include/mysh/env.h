/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** env.h
*/

#ifndef INC_42SH_ENV_H
    #define INC_42SH_ENV_H

    #include "mysh.h"

typedef struct env_s {
    char **env;
} env_t;

//
// Initialisation
//

/**
 * @brief Load the environment
 *
 * @param env The environment
 * @return env_t* The new environment
 */
env_t *load_env(char **env);

/**
 * @brief Duplicate the environment
 *
 * @param env The environment
 * @return char** The new environment
 */
char **dup_env(char **env);

/**
 * @brief Fix the environment
 *
 * @param env The environment
 * @return char** The new environment
 */
char **fix_env(char **env);

//
// Destroy
//

/**
 * @brief Destroy the environment
 *
 * @param env The environment
 * @return int The status
 */
int destroy_env(mysh_t *context);

//
// Environment functions
//

/**
 * @brief Get an environment variable
 *
 * @param env The environment
 * @param name The name of the variable
 * @return char* The value of the variable
 */
char *get_env(mysh_t *context, char *name);

/**
 * @brief Set an environment variable
 *
 * @param env The environment
 * @param name The name of the variable
 * @param value The value of the variable
 * @return char** The new environment
 */
char **set_env(mysh_t *context, char *name, char *value) ;

/**
 * @brief Unset an environment variable
 *
 * @param env The environment
 * @param name The name of the variable
 * @return char** The new environment
 */
char **unset_env(mysh_t *context, char *name);

/**
 * @brief Display the environment
 *
 * @param env The environment
 * @return bool True if write failed
 */
bool display_env(mysh_t *context);

/**
 * @brief Set exit as true adn set the status as 1
 *
 * @param env The environment
 * @return env_t* The new environment
 */
void exit_env(mysh_t *context);

#endif /* !INC_42SH_ENV_H */
