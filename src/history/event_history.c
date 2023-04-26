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

static void handle_precise_event(char **av, mysh_t *context)
{
    size_t cmd_size = ice_strlen(av[0]) - 1;
    int j = 0;
    char *str1 = malloc(sizeof(char) * (cmd_size + 1));
    int nb_event;
    history_t *tmp;

    for (int i = 1; av[0][i] != '\0'; i++, j++)
        str1[j] = av[0][i];
    str1[j] = '\0';
    nb_event = ice_atoi(str1);
    for (list_node_t *node = context->history->tail; node != NULL;
    node = node->prev) {
        tmp = node->value;
        if (nb_event == tmp->index) {
            ice_printf("%s\n", tmp->cmd);
            handle_pipe(tmp->cmd, context);
        }
    }
}

static void handle_last_event(char **av, mysh_t *context)
{
    history_t *tmp;
    list_node_t *node = context->history->tail;

    if (node == NULL)
        return;
    tmp = node->value;
    if (av[0][1] == '!' && av[0][2] == '\0') {
        ice_printf("%s\n", tmp->cmd);
        handle_pipe(tmp->cmd, context);
    }
}

static int search_in_history(char **av, char *cmd, mysh_t *context)
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
    return 0;
}

bool event_history(char **av, mysh_t *context)
{
    history_t *tmp;

    handle_precise_event(av, context);
    handle_last_event(av, context);
    for (list_node_t *node = context->history->tail; node != NULL;
    node = node->prev) {
        tmp = node->value;
        if (search_in_history(av, tmp->cmd, context) == 1)
            break;
    }
    return (STATUS = 1);
}
