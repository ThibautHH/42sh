/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_sequence.c
*/

#include "ice/array.h"
#include "ice/string.h"
#include "mysh/parser.h"

bool handle_sequence(char *buffer, env_t *env)
{
    char **sequence = ice_strsplit(buffer, ";");

    if (!sequence)
        return true;
    for (int i = 0; sequence[i]; i++)
        if (handle_pipe(sequence[i], env))
            return true;
    ice_free_array((void **)sequence);
    return false;
}
