/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** handle_sequence.c
*/

#include "ice/array.h"
#include "ice/string.h"
#include "redirection.h"

bool handle_sequence(char *buffer, env_t *env)
{
    char **sequence = ice_strsplit(buffer, ";");

    if (!sequence)
        return true;
    for (int i = 0; sequence[i]; i++)
        if (handle_pipe(env, sequence[i]))
            return true;
    ice_free_array((void **)sequence);
    return false;
}
