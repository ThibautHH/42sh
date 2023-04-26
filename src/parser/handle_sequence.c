/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_sequence.c
*/

#include "ice/array.h"
#include "mysh/parser.h"
#include "mysh/parser_commands.h"
#include "mysh/history.h"

bool handle_sequence(char *buffer, mysh_t *context)
{
    char **sequence = parse_command_line(buffer);

    get_history_data(buffer, context);
    if (!sequence)
        return true;
    for (int i = 0; sequence[i]; i++)
        if (handle_pipe(sequence[i], context))
            return true;
    ice_free_array((void **)sequence);
    return false;
}
