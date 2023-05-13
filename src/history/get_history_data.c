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
    time_t curr_time;
    void *times;

    if (!history || buffer[0] == '!' || buffer[0] == '\n')
        return;
    if (time(&curr_time) == -1)
        DIE;
    times = localtime(&curr_time);
    if (!times)
        DIE;
    times = asctime(times);
    if (!times)
        DIE;
    *history = (history_t){ice_strdup(buffer),
        HISTORY->size + 1, times + 11, 0};
    history->date[5] = '\0';
    if (!history->cmd || !list_add(HISTORY, history))
        DIE;
}
