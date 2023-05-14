/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history
*/

#ifndef HISTORY_H_
    #define HISTORY_H_

    #include "mysh.h"

    #define EVENT_NOT_FOUND_ID ((event_id >= 0) ? event_id : event_id + 1)

typedef struct history_s {
    char *cmd;
    int index;
    char date[6];
    int check;
} history_t;

void get_history_data(char *buffer, mysh_t *context);
bool expand_history(mysh_t *context);
void free_history(history_t *node);

static inline bool handle_history(mysh_t *context)
{
    int ret;

    if (((ret = handle_precise_event(context)) >= 0)
        || ((ret = handle_search_event(context)) >= 0)
        || ((ret = handle_prefix_event(context)) >= 0))
        return ret;
    return false;
}

#endif
