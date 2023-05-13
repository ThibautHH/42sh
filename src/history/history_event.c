/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_event
*/

#include <stdlib.h>
#include <stdio.h>

#include "mysh.h"
#include "mysh/history.h"
#include "ice/int.h"

static int handle_precise_event(mysh_t *context, int offset)
{
    size_t cmd_size = ice_strlen(LINE) - 2;
    int j = 0;
    char *str = malloc(sizeof(char) * (cmd_size + 2));
    history_t *tmp;

    if (LINE[1] != '?' || str == NULL) return 1;
    for (int i = 2; LINE[i] != '\0' && LINE[i] != '?'; i++, j++)
        str[j] = LINE[i];
    str[j] = '\0';
    for (list_node_t *node = HISTORY->tail; node != NULL;
        node = node->prev) {
        tmp = node->value;
        if (ice_strstr(tmp->cmd, str) != NULL) {
            realloc_line(context, tmp->cmd, offset);
            printf("%s\n", LINE);
            return 0;
        }
    }
    printf("%s: Event not found.\n", str);
    return 0;
}

static int handle_search_event(mysh_t *context, int offset)
{
    int nb_event = ice_atoi(LINE + 1);
    history_t *tmp;

    if (nb_event <= 0)
        return 1;
    for (list_node_t *node = HISTORY->tail; node != NULL;
        node = node->prev) {
        tmp = node->value;
        if (nb_event == tmp->index) {
            realloc_line(context, tmp->cmd, offset);
            printf("%s\n", LINE);
            return 0;
        }
    }
    printf("%s: Event not found.\n", LINE + 1);
    return 1;
}

static int handle_last_event(mysh_t *context, int offset)
{
    history_t *tmp;
    list_node_t *node = HISTORY->tail;

    if (node == NULL)
        return 0;
    tmp = node->value;
    if (LINE[1] == '!' && LINE[2] == '\0') {
        realloc_line(context, tmp->cmd, offset);
        printf("%s\n", LINE);
        return 0;
    }
    return 1;
}

static int search_in_history(char *cmd, mysh_t *context, int offset,
    ull_t count)
{
    size_t cmd_size = ice_strlen(LINE) - 1;
    char *str1 = malloc(sizeof(char) * (cmd_size + 1));
    char *str2 = malloc(sizeof(char) * (cmd_size + 1));

    if (str1 == NULL || str2 == NULL)
        return 0;
    ice_strcpy(str1, LINE + 1);
    ice_strncpy(str2, cmd, cmd_size);
    if (ice_strcmp(str2, str1) == 0) {
        realloc_line(context, cmd, offset);
        printf("%s\n", LINE);
        return 1;
    }
    if (count > HISTORY->size)
        printf("%s: Event not found.\n", str1);
    return 0;
}

void history_event(mysh_t *context, int offset)
{
    history_t *tmp;
    ull_t count = 0;

    if (handle_precise_event(context, offset) == 0)
        return;
    if (handle_search_event(context, offset) == 0)
        return;
    if (handle_last_event(context, offset) == 0)
        return;
    for (list_node_t *node = HISTORY->tail; node != NULL;
    node = node->prev, count++) {
        tmp = node->value;
        if (search_in_history(tmp->cmd, context, offset, count) == 1)
            break;
    }
    return;
}
