/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Parsing inline functions
*/

#ifndef PARSING_FUNCTIONS_H_
    #define PARSING_FUNCTIONS_H_

    #include "mysh.h"

static inline _Bool is_char_escaped(mysh_t *context)
{
    size_t escape_count = 0;

    for (; P > S && P[-1] == '\\'; P--)
        escape_count++;
    return (escape_count & 1);
}

static inline void get_ppl_separator(mysh_t *context)
{
    if (IS_CHAR_ESCAPED)
        return;
    pplsep_t tmp = PPLSEP;
    PPLSEP = PPLSEP_NONE;
    for (uint8_t i = 0; i < PPLSEPC; i++)
        if (_IS_PPLSEP_STR) {
            PPLSEP = i;
            break;
        }
    if (PPLSEP != PPLSEP_NONE)
        LAST_PPLSEP = tmp;
}

static inline void to_next_token(mysh_t *context)
{
    while (*P && IS_SEPARATOR)
        P++;
}

static inline void to_token_end(mysh_t *context)
{
    for (char *q = NULL; *P && (q || !(IS_SEPARATOR || IS_PPLSEP)); P++)
        if (IS_QUOTE(*P))
            q = (q == P) ? NULL : P;
}

#endif /* !PARSING_FUNCTIONS_H_ */
