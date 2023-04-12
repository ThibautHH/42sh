/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** mysh.h
*/

#ifndef MYSH_H
    #define MYSH_H

    #include <stdbool.h>

    #include "ice/macro.h"

    #define IS_END(x) ((x == '\0') || (x == '\n'))
    #define IS_SPACE(x) ((x == ' ') || (x == '\t'))

typedef struct env_s {
    char **env;
    int status;
    bool exit;
} env_t;

#endif /* !MYSH_H */
