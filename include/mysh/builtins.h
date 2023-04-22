/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtins.h
*/

#ifndef MINISHELL1_BUILTINS_H
    #define MINISHELL1_BUILTINS_H

    #include "mysh.h"

//
// Builtins
//

/**
 * @brief Change the current working directory
 *
 * @param path The path to change to
 * @param env The environment
 * @return env The new environment
 */
bool builtin_cd(char **av, mysh_t *context);

/**
 * @brief Exit the shell
 *
 * @param av The arguments
 * @param env The environment
 * @return env The new environment
 */
bool builtin_exit(UNUSED char **av, mysh_t *context);

/**
 * @brief Display the environment
 *
 * @param env The environment
 * @return env The new environment
 */
bool builtin_env(UNUSED char **av, mysh_t *context);

/**
 * @brief Set an environment variable
 *
 * @param av The arguments
 * @param env The environment
 * @return env The new environment
 */
bool builtin_setenv(char **av, mysh_t *context);

/**
 * @brief Unset an environment variable
 *
 * @param av The arguments
 * @param env The environment
 * @return env The new environment
 */
bool builtin_unsetenv(char **av, mysh_t *context);

//
// Structs
//

typedef struct builtin_s {
    char *name;
    bool (*func)(char **, mysh_t *);
} builtin_t;

static const builtin_t builtins[] = {
    {"cd", builtin_cd},
    {"exit", builtin_exit},
    {"env", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {NULL, NULL}
};

#endif /* !MINISHELL1_BUILTINS_H */
