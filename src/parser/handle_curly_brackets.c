/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_curly_brackets
*/

#include "mysh.h"
#include "mysh/parsing_functions.h"

#include <stdio.h>

static _Bool search_end(mysh_t *context, int off)
{
    for (int i = off + 1; LINE[i] != '\0'; i++) {
        if (LINE[i] == '}')
            return true;
        if (!IS_ALPHANUM(LINE[i])) {
            dprintf(2, "Missing '}'.\n");
            return false;
        }
    }
    return false;
}

_Bool handle_curly(mysh_t *context)
{
    for (int i = 0; LINE[i] != '\0'; i++) {
        if (LINE[i] != '{')
            continue;
        P = LINE + i + 1;
        if (IS_SEPARATOR || *P == '\n')
            continue;
        if (search_end(context, i) == false)
            return false;
    }
    return true;
}
