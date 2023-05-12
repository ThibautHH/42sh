/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_curly_brackets
*/

#include <stdio.h>

#include "mysh/parsing_functions.h"

static bool search_end(mysh_t *context, int off)
{
    for (int i = off + 1; LINE[i] != '\0'; i++) {
        if (LINE[i] == '}')
            return true;
        if (IS_ALPHANUM(LINE[i]))
            continue;
        if (fprintf(stderr, "Missing '}'.\n") < 0)
            DIE;
        return false;
    }
    return false;
}

bool handle_curly_brackets(mysh_t *context)
{
    for (int i = 0; LINE[i] != '\0'; i++) {
        if (LINE[i] != '{')
            continue;
        P = LINE + i + 1;
        if (IS_SEPARATOR || *P == '\n')
            continue;
        if (search_end(context, i) == false) {
            STATUS = 1;
            return false;
        }
    }
    return true;
}
