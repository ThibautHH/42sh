/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_history_data
*/

#include <time.h>
#include <stdlib.h>

#include "mysh.h"

static char *get_date(char *date)
{
    char *r_date = malloc(sizeof(char) * 6);

    for (int i = 0, j = 0; i < 16; i++)
        if (i >= 11 && i < 16) {
            r_date[j] = date[i];
            j++;
        }
    r_date[5] = '\0';
    return r_date;
}

void get_history_data(char *buffer, env_t *env, history_t *history)
{
    time_t curr_time;
    char *times;

    if (buffer[0] == '!')
        return;
    time(&curr_time);
    times = ice_strdup(asctime(localtime(&curr_time)));
    history->date = get_date(times);
    history->cmd = ice_strdup(buffer);
    history->index = env->history->size + 1;
    list_add(env->history, history);
}
