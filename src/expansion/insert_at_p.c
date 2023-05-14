/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Command line insertion
*/

#include <string.h>

#include "mysh.h"

void insert_at_p(mysh_t *context, char *str, size_t len)
{
    size_t str_len = strlen(str);
    size_t new_line_len = LEN + 1 + str_len - len;
    size_t p_off = P - LINE;
    char *tmp;

    str[str_len - 1] = 0;
    if (new_line_len > LINESZ) {
        LINESZ = len;
        LINE = realloc(LINE, LINESZ);
        if (!LINE)
            DIE;
        P = LINE + p_off;
    }
    tmp = strdup(P + len);
    if (!tmp)
        DIE;
    sprintf(P, "%s%s", str, tmp);
    P += str_len;
    str[str_len - 1] = '\n';
    free(tmp);
}
