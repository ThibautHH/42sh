/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Parsing functions
*/

#include <string.h>

#include "mysh.h"

bool is_char_escaped(mysh_t *context)
{
    size_t escape_count = 0;

    if (!P || !*P)
        return false;
    for (char *p = P; p > S && p[-1] == '\\'; p--)
        escape_count++;
    return (escape_count & 1);
}

void get_ppl_separator(mysh_t *context)
{
    if (IS_CHAR_ESCAPED)
        return;
    pplsep_t tmp = PPLSEP;
    PPLSEP = PPLSEP_NONE;
    for (uint8_t i = 0; i < PPLSEPC; i++)
        if (IS_PPLSEP_STR) {
            PPLSEP = i;
            break;
        }
    if (PPLSEP != PPLSEP_NONE)
        LAST_PPLSEP = tmp;
}

void to_next_token(mysh_t *context)
{
    while (*P && IS_SEPARATOR)
        P++;
}

bool unquote(mysh_t *context)
{
    size_t len = 0;
    char *s = P;

    if (!IS_QUOTE(*P))
        return false;
    for (char q = *P; *(++P) && (*P != q || IS_CHAR_ESCAPED);)
        len++;
    ice_strncpy2(s, s + 1, len);
    P++;
    ice_strncpy2(s + len, P, strlen(P) + 1);
    P = s + len;
    return true;
}

void to_token_end(mysh_t *context)
{
    for (char *q = NULL; *P && (q || !(IS_SEPARATOR || IS_PPLSEP)); P++)
        if (IS_QUOTE(*P) && !IS_CHAR_ESCAPED)
            q = q ? ((*q == *P) ? NULL : q) : P;
}
