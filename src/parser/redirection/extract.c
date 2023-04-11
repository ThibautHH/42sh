/*
** EPITECH PROJECT, 2023
** mysh
** File description:
** extract.c
*/

#include <malloc.h>

#include "mysh.h"
#include "ice/string.h"
#include "redirection.h"

ui_t extract_len(const char *str, char end)
{
    ui_t len = 0;

    for (; str[len] && str[len] != end; len++);
    return len;
}

bool extract_output(redir_t *redir, char *str, char *start)
{
    char *p = ice_strstr(str, start);
    ui_t i = 0;

    if (!p)
        return false;
    for (; i < (ui_t)ice_strlen(start); i++)
        p[i] = ' ';
    redir->file_out = malloc(sizeof(char) * extract_len(p, '<') + 1);
    if (!redir->file_out)
        return false;
    for (i = 0; p[i] && p[i] != '<'; i++) {
        redir->file_out[i] = p[i];
        p[i] = ' ';
    }
    redir->file_out[i] = '\0';
    ice_strtrim(redir->file_out);
    return true;
}

bool extract_input(redir_t *redir, char *str, char *start)
{
    char *p = ice_strstr(str, start);
    ui_t i = 0;

    if (!p)
        return false;
    for (; i < (ui_t)ice_strlen(start); i++)
        p[i] = ' ';
    redir->file_in = malloc(sizeof(char) * extract_len(p, '>') + 1);
    if (!redir->file_in)
        return false;
    for (i = 0; p[i] && p[i] != '>'; i++) {
        redir->file_in[i] = p[i];
        p[i] = ' ';
    }
    redir->file_in[i] = '\0';
    ice_strtrim(redir->file_in);
    return true;
}
