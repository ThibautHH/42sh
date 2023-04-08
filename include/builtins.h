/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** builtins.h
*/

#ifndef MINISHELL1_BUILTINS_H
    #define MINISHELL1_BUILTINS_H

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
