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
void builtin_alias(mysh_t *context);
void builtin_unalias(mysh_t *context);

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
};

#endif /* !BUILTINS_H */
