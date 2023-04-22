/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_unsetenv.c
*/

#include "ice/array.h"

#include "mysh.h"
#include "mysh/miscellaneous.h"

bool builtin_unsetenv(char **av, mysh_t *context)
{
    size_t argc = ice_array_len((void **) av);
    if (argc != 2) {
        if (argc < 2) {
            DWRITE(STDERR_FILENO, "unsetenv: Too few arguments.\n", 29);
        } else
            DWRITE(STDERR_FILENO, "unsetenv: Too many arguments.\n", 30);
        return (STATUS = 1);
    }
    env_remove(context, av[1]);
    return (STATUS = 0);
}
