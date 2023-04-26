/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtins.h
*/

#ifndef BUILTINS_H
    #define BUILTINS_H

    #define BUILTIN_COUNT 5
    #include "mysh/history.h"

    #include <stdbool.h>

typedef enum {
    BUILDIN_NONE = -1,
    BUILTIN_CD,
    BUILTIN_EXIT,
    BUILTIN_ENV,
    BUILTIN_SETENV,
    BUILTIN_UNSETENV
} builtin_t;

typedef struct event_s {
    char *name;
    bool (*func)(char **, mysh_t *);
} builtin_t;

typedef struct mysh_s mysh_t;

void builtin_cd(mysh_t *context);
void builtin_exit(mysh_t *context);
void builtin_env(mysh_t *context);
void builtin_setenv(mysh_t *context);
void builtin_unsetenv(mysh_t *context);

static const struct {
    char *name;
    builtin_t id;
    void (*builtin)(mysh_t *);
} BUILTINS[BUILTIN_COUNT] = {
    {"cd", BUILTIN_CD, builtin_cd},
    {"exit", BUILTIN_EXIT, builtin_exit},
    {"env", BUILTIN_ENV, builtin_env},
    {"setenv", BUILTIN_SETENV, builtin_setenv},
    {"unsetenv", BUILTIN_UNSETENV, builtin_unsetenv}
static const builtin_t builtins[] = {
    {"cd", builtin_cd},
    {"exit", builtin_exit},
    {"env", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {"history", builtin_history},
    {NULL, NULL}
};

static const event_t event[] = {
    {"!", event_history},
    {NULL, NULL}
};

#endif /* !BUILTINS_H */
