/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_history_data
*/

#include <time.h>
#include <stdlib.h>

#include "mysh.h"
#include "mysh/history.h"
#include "list.h"

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

void get_history_data(char *buffer, mysh_t *context)
{
    time_t curr_time;
    char *times;
    history_t *tmp = malloc(sizeof(history_t));

    if (buffer[0] == '!' || buffer[0] == '\n')
        return;
    time(&curr_time);
    times = ice_strdup(asctime(localtime(&curr_time)));
    tmp->date = get_date(times);
    tmp->cmd = ice_strdup(buffer);
    tmp->index = HISTORY->size + 1;
    list_add(HISTORY, tmp);
}
