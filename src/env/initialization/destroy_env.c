/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** destroy_env.c
*/

#include <malloc.h>

#include "mysh.h"
#include "ice/array.h"

int destroy_env(env_t *env)
{
    int exit_status = env->status;

    ice_free_array((void **)env->env);
    free(env);
    return exit_status;
}
