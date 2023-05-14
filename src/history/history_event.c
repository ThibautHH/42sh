/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_event
*/

#include <stdio.h>
#include <string.h>

#include "mysh/history.h"

static bool handle_search_event(mysh_t *context, int offset)
{
    char *str = malloc(sizeof(char) * (strlen(LINE) - 1));
    int j = 0;

    for (int i = 2; LINE[i]; i++, j++)
        str[j] = LINE[i];
    str[j - 1] = '\0';
    if (!str || LINE[1] != '?')
        return true;
    for (list_node_t *node = HISTORY->tail; node; node = node->prev) {
        if (strstr(((history_t *)node->value)->cmd, str)) {
            realloc_line(context, ((history_t *)node->value)->cmd, offset);
            PRINT(LINE);
            free(str);
            return false;
        }
    }
    ERRPRINT("%s: Event not found.\n", str);
    free(str);
    return false;
}

static bool handle_precise_event(mysh_t *context, int offset)
{
    char *endptr;
    long nb_event = strtol(LINE + 1, &endptr, 10);

    if (*endptr || nb_event < 0)
        return true;
    for (list_node_t *node = HISTORY->tail; node; node = node->prev) {
        if (nb_event == ((history_t *)node->value)->index) {
            realloc_line(context, ((history_t *)node->value)->cmd, offset);
            PRINT(LINE);
            return false;
        }
    }
    ERRPRINT("%ld: Event not found.\n", nb_event);
    return true;
}

static bool handle_last_event(mysh_t *context, int offset)
{
    list_node_t *node = HISTORY->tail;

    if (!node)
        return false;
    if (LINE[0] == '!' && LINE[1] == '!' && !LINE[2]) {
        realloc_line(context, ((history_t *)node->value)->cmd, offset);
        PRINT(LINE);
        return false;
    }
    return true;
}

static bool search_in_history(mysh_t *context, int offset)
{
    uint32_t len;
    char *str;

    for (len = 0; !IS_WHITESPACE(LINE[len]); len++);
    str = ice_strndup(LINE + 1, len - 1);
    if (!str)
        DIE;
    for (list_node_t *node = HISTORY->tail; node; node = node->prev)
        if (!strncmp(str, ((history_t *)node->value)->cmd, len - 1)) {
            realloc_line(context, ((history_t *)node->value)->cmd, offset);
            PRINT(LINE);
            free(str);
            return true;
        }
    ERRPRINT("%s: Event not found.\n", str);
    free(str);
    return false;
}

void history_event(mysh_t *context, int offset)
{
    if (!handle_last_event(context, offset)
        || !handle_precise_event(context, offset)
        || !handle_search_event(context, offset)
        || !search_in_history(context, offset))
        return;
}
