/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** builtins.h
*/

#ifndef MINISHELL1_BUILTINS_H
    #define MINISHELL1_BUILTINS_H

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
env_t *builtin_cd(char **av, env_t *env);

/**
 * @brief Exit the shell
 *
 * @param av The arguments
 * @param env The environment
 * @return env The new environment
 */
env_t *builtin_exit(UNUSED char **av, env_t *env);

/**
 * @brief Display the environment
 *
 * @param env The environment
 * @return env The new environment
 */
env_t *builtin_env(UNUSED char **av, env_t *env);

/**
 * @brief Set an environment variable
 *
 * @param av The arguments
 * @param env The environment
 * @return env The new environment
 */
env_t *builtin_setenv(char **av, env_t *env);

/**
 * @brief Unset an environment variable
 *
 * @param av The arguments
 * @param env The environment
 * @return env The new environment
 */
env_t *builtin_unsetenv(char **av, env_t *env);

//
// Structs
//

typedef struct builtin_s {
    char *name;
    env_t *(*func)(char **, env_t *);
} builtin_t;

const builtin_t builtins[] = {
    {"cd", builtin_cd},
    {"exit", builtin_exit},
    {"env", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {NULL, NULL}
};

#endif /* !MINISHELL1_BUILTINS_H */
