/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_history_data
*/

#include <time.h>

#include "mysh/history.h"

void get_history_data(char *buffer, mysh_t *context)
{
    history_t *history = malloc(sizeof(history_t));
    time_t t;
    struct tm *tm;
    char *tstr;

    if (!history || time(&t) == -1
        || !(tm = localtime(&t))
        || !(tstr = asctime(tm)))
        DIE;
    history->cmd = ice_strdup(buffer);
    history->index = HISTORY->size + 1;
    ice_strncpy2(history->date, tstr + 11, 5);
    history->date[5] = '\0';
    if (!history->cmd || !list_add(HISTORY, history))
        DIE;
}
