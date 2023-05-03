/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** extract.c
*/

#include <malloc.h>

#include "ice/string.h"
#include "mysh/redirection.h"

static ui_t extract_len(const char *str, char end)
{
    ui_t len = 0;

    for (; str[len] && str[len] != end; len++);
    return len;
}

bool extract_output(redirs_t *redirs, char *str, char *start)
{
    char *p = ice_strstr(str, start);
    ui_t i = 0;

    if (!p)
        return false;
    for (; i < (ui_t)ice_strlen(start); i++)
        p[i] = ' ';
    redirs->file_out = malloc(sizeof(char) * extract_len(p, '<') + 1);
    if (!redirs->file_out)
        return false;
    for (i = 0; p[i] && p[i] != '<'; i++) {
        redirs->file_out[i] = p[i];
        p[i] = ' ';
    }
    redirs->file_out[i] = '\0';
    ice_strtrim(redirs->file_out);
    return true;
}

bool extract_input(redirs_t *redirs, char *str, char *start)
{
    char *p = ice_strstr(str, start);
    ui_t i = 0;

    if (!p)
        return false;
    for (; i < (ui_t)ice_strlen(start); i++)
        p[i] = ' ';
    redirs->file_in = malloc(sizeof(char) * extract_len(p, '>') + 1);
    if (!redirs->file_in)
        return false;
    for (i = 0; p[i] && p[i] != '>'; i++) {
        redirs->file_in[i] = p[i];
        p[i] = ' ';
    }
    redirs->file_in[i] = '\0';
    ice_strtrim(redirs->file_in);
    return true;
}
