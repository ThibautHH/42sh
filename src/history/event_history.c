/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_event
*/

#include <stdlib.h>

#include "mysh.h"
#include "mysh/parser.h"
#include "mysh/redirection.h"
#include "ice/int.h"

static int handle_precise_event(char **av, mysh_t *context)
{
    size_t cmd_size = ice_strlen(av[0]) - 2;
    int j = 0;
    char *str = malloc(sizeof(char) * (cmd_size + 2));
    history_t *tmp;

    if (av[0][1] != '?' || str == NULL) return 1;
    for (int i = 2; av[0][i] != '\0' && av[0][i] != '?'; i++, j++)
        str[j] = av[0][i];
    str[j] = '\0';
    for (list_node_t *node = context->history->tail; node != NULL;
    node = node->prev) {
        tmp = node->value;
        if (ice_strstr(tmp->cmd, str) != NULL) {
            ice_printf("%s\n", tmp->cmd);
            handle_pipe(tmp->cmd, context);
            return 0;
        }
    }
    ice_printf("%s: Event not found.\n", str);
    return 0;
}

static int handle_search_event(char **av, mysh_t *context)
{
    int nb_event = ice_atoi(av[0] + 1);
    history_t *tmp;

    for (list_node_t *node = context->history->tail; node != NULL;
    node = node->prev) {
        tmp = node->value;
        if (nb_event == tmp->index) {
            ice_printf("%s\n", tmp->cmd);
            handle_pipe(tmp->cmd, context);
            return 0;
        }
    }
    ice_printf("%s: Event not found.\n", av[0] + 1);
    return 1;
}

static int handle_last_event(char **av, mysh_t *context)
{
    history_t *tmp;
    list_node_t *node = context->history->tail;

    if (node == NULL)
        return 0;
    tmp = node->value;
    if (av[0][1] == '!' && av[0][2] == '\0') {
        ice_printf("%s\n", tmp->cmd);
        handle_pipe(tmp->cmd, context);
        return 0;
    }
    return 1;
}

static int search_in_history(char **av, char *cmd, mysh_t *context,
ull_t count)
{
    size_t cmd_size = ice_strlen(av[0]) - 1;
    int j = 0;
    char *str1 = malloc(sizeof(char) * (cmd_size + 1));
    char *str2 = malloc(sizeof(char) * (cmd_size + 1));

    for (int i = 1; av[0][i] != '\0'; i++, j++)
        str1[j] = av[0][i];
    str1[j] = '\0';
    ice_strncpy(str2, cmd, cmd_size);
    if (ice_strcmp(str2, str1) == 0) {
        ice_printf("%s\n", cmd);
        handle_pipe(cmd, context);
        return 1;
    }
    if (count == context->history->size)
        ice_printf("%s: Event not found.\n", str1);
    return 0;
}

bool event_history(char **av, mysh_t *context)
{
    history_t *tmp;
    ull_t count = 0;

    if (handle_precise_event(av, context) == 0)
        return (STATUS = 1);
    if (handle_search_event(av, context) == 0)
        return (STATUS = 1);
    if (handle_last_event(av, context) == 0)
        return (STATUS = 1);
    for (list_node_t *node = context->history->tail; node != NULL;
    node = node->prev, count++) {
        tmp = node->value;
        if (search_in_history(av, tmp->cmd, context, count) == 1)
            break;
    }
    return (STATUS = 1);
}
