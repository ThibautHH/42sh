/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** expand_history
*/

#include <stdio.h>
#include <string.h>

#include "mysh/history.h"
#include "mysh/parsing_functions.h"

static int handle_search_event(mysh_t *context)
{
    size_t kwlen;
    char *kw;
    list_node_t *node = HISTORY->tail;

    if (P[1] != '?')
        return -1;
    kwlen = ice_strtil(P + 2, '?');
    kw = strndup(P + 2, kwlen);
    for (; node; node = node->prev)
        if (strstr(((history_t *)node->value)->cmd, kw))
            break;
    if (node)
        insert_at_p(context, ((history_t *)node->value)->cmd, kwlen + 3);
    else
        ERRPRINT("%s: Event not found.\n", kw);
    free(kw);
    return !!node;
}

static void select_node(list_node_t **node, long event_id)
{
    if (event_id < 0) {
        for (size_t i = 1; i < (ul_t)-event_id && *node; i++)
            *node = (*node)->prev;
        return;
    }
    for (; *node; *node = (*node)->prev)
        if (event_id == ((history_t *)(*node)->value)->index)
            break;
}

static int handle_precise_event(mysh_t *context)
{
    list_node_t *node = HISTORY->tail;
    char *ptmp = P;
    long event_id;
    size_t len;
    bool is_prev = false;

    if (P[1] == '!')
        event_id = ((is_prev = true), -1);
    else
        event_id = strtol(P + 1, &P, 10);
    len = is_prev ? 2 : P - ptmp;
    if (!is_prev && !IS_WHITESPACE(*P) && (P = ptmp, 1))
        return -1;
    P = ptmp;
    select_node(&node, event_id);
    if (node)
        insert_at_p(context, ((history_t *)node->value)->cmd, len);
    else
        ERRPRINT("%ld: Event not found.\n", EVENT_NOT_FOUND_ID);
    return !!node;
}

static int handle_prefix_event(mysh_t *context)
{
    char *prefix, *ptmp = P;
    size_t prefix_len;
    list_node_t *node = HISTORY->tail;

    TO_TOKEN_END;
    prefix_len = P - (ptmp + 1);
    P = ptmp;
    prefix = strndup(P + 1, prefix_len);
    for (; node; node = node->prev)
        if (strncmp(prefix, ((history_t *)node->value)->cmd, prefix_len) == 0)
            break;
    if (node)
        insert_at_p(context, ((history_t *)node->value)->cmd, prefix_len + 1);
    else
        ERRPRINT("%s: Event not found.\n", prefix);
    free(prefix);
    return !!node;
}

static bool handle_history(mysh_t *context)
{
    int ret;

    if (((ret = handle_precise_event(context)) >= 0)
        || ((ret = handle_search_event(context)) >= 0)
        || ((ret = handle_prefix_event(context)) >= 0))
        return ret;
    return false;
}

bool expand_history(mysh_t *context)
{
    bool is_event = true;

    for (P = LINE; *P; P++)
        if (*P == '!' && !IS_WHITESPACE(P[1]) && !IS_CHAR_ESCAPED
            && !(is_event = false) && !handle_history(context))
            return false;
    if (is_event)
        get_history_data(LINE, context);
    else
        PRINT(LINE);
    return true;
}
