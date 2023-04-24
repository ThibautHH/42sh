/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtins.h
*/

#ifndef BUILTINS_H
    #define BUILTINS_H

    #define BUILTIN_COUNT 5

    #include <stdbool.h>

typedef enum {
    BUILDIN_NONE = -1,
    BUILTIN_CD,
    BUILTIN_EXIT,
    BUILTIN_ENV,
    BUILTIN_SETENV,
    BUILTIN_UNSETENV
} builtin_t;

typedef struct mysh_s mysh_t;

bool builtin_cd(mysh_t *context);
bool builtin_exit(mysh_t *context);
bool builtin_env(mysh_t *context);
bool builtin_setenv(mysh_t *context);
bool builtin_unsetenv(mysh_t *context);

static const struct {
    char *name;
    builtin_t id;
    bool (*builtin)(mysh_t *);
} BUILTINS[BUILTIN_COUNT] = {
    {"cd", BUILTIN_CD, builtin_cd},
    {"exit", BUILTIN_EXIT, builtin_exit},
    {"env", BUILTIN_ENV, builtin_env},
    {"setenv", BUILTIN_SETENV, builtin_setenv},
    {"unsetenv", BUILTIN_UNSETENV, builtin_unsetenv}
};

#endif /* !BUILTINS_H */
