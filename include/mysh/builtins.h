/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtins.h
*/

#ifndef BUILTINS_H
    #define BUILTINS_H

    #define BUILTIN_COUNT 7

    #include <stdbool.h>

typedef enum {
    BUILDIN_NONE = -1,
    BUILTIN_CD,
    BUILTIN_EXIT,
    BUILTIN_ENV,
    BUILTIN_SETENV,
    BUILTIN_UNSETENV,
    BUILTIN_ALIAS,
    BUILTIN_UNALIAS
} builtin_t;

typedef struct mysh_s mysh_t;

void builtin_cd(mysh_t *context);
void builtin_exit(mysh_t *context);
void builtin_env(mysh_t *context);
void builtin_setenv(mysh_t *context);
void builtin_unsetenv(mysh_t *context);
bool builtin_alias(char **av, mysh_t *context);
bool builtin_unalias(char **av, mysh_t *context);

static const struct {
    char *name;
    builtin_t id;
    void (*builtin)(mysh_t *);
} BUILTINS[BUILTIN_COUNT] = {
    {"cd", BUILTIN_CD, builtin_cd},
    {"exit", BUILTIN_EXIT, builtin_exit},
    {"env", BUILTIN_ENV, builtin_env},
    {"setenv", BUILTIN_SETENV, builtin_setenv},
    {"unsetenv", BUILTIN_UNSETENV, builtin_unsetenv},
    {"alias", BUILTIN_ALIAS, builtin_alias},
    {"unalias", BUILTIN_UNALIAS, builtin_unalias}
}

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

/**
 * @brief Create an alias
 *
 * @param av The arguments
 * @param context Main struct of mysh
 * @return bool return false when an error happen
 */
bool builtin_alias(char **av, mysh_t *context);

/**
 * @brief Remove an alias
 *
 * @param av The arguments
 * @param context Main struct of mysh
 * @return bool always true
 */
bool builtin_unalias(char **av, mysh_t *context);

#endif /* !BUILTINS_H */
