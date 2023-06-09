/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_curly_brackets
*/

#include <stdio.h>

#include "mysh/parsing_functions.h"

static bool search_end(mysh_t *context, size_t off)
{
    for (size_t i = off + 1; LINE[i]; i++) {
        if (LINE[i] == '}')
            return true;
        if (IS_ALPHANUM(LINE[i]))
            continue;
        ERRPRINT("Missing '}'.\n");
        return false;
    }
    return false;
}

bool handle_curly_brackets(mysh_t *context)
{
    for (size_t i = 1; LINE[i]; i++) {
        if (!(LINE[i - 1] == '$' && LINE[i] == '{'))
            continue;
        P = LINE + i + 1;
        if (IS_SEPARATOR || *P == '\n')
            continue;
        if (!search_end(context, i)) {
            STATUS = 1;
            return false;
        }
    }
    return true;
}
