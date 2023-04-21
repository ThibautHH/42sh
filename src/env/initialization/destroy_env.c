/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** destroy_env.c
*/

#include <malloc.h>

#include "mysh/env.h"
#include "ice/array.h"

int destroy_env(mysh_t *context)
{
    int exit_status = STATUS;

    ice_free_array((void **)ENV->env);
    free(ENV);
    return exit_status;
}
