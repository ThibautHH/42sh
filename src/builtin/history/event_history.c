/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_event
*/

#include <stdlib.h>

#include "mysh.h"
#include "ice/int.h"
#include "redirection.h"

static void handle_precise_event(char **av, env_t *env)
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
    for (list_node_t *node = env->history->tail; node != NULL;
    node = node->prev) {
        tmp = node->value;
        if (nb_event == tmp->index) {
            ice_printf("%s\n", tmp->cmd);
            handle_pipe(env, tmp->cmd);
        }
    }
}

static void handle_last_event(char **av, env_t *env)
{
    history_t *tmp;
    list_node_t *node = env->history->tail;

    if (node == NULL)
        return;
    tmp = node->value;
    if (av[0][1] == '!' && av[0][2] == '\0') {
        ice_printf("%s\n", tmp->cmd);
        handle_pipe(env, tmp->cmd);
    }
}

static int search_in_history(char **av, char *cmd, env_t *env)
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
        handle_pipe(env, cmd);
        return 1;

    }
    return 0;
}

env_t *event_history(char **av, env_t *env)
{
    history_t *tmp;

    handle_precise_event(av, env);
    handle_last_event(av, env);
    for (list_node_t *node = env->history->tail; node != NULL;
    node = node->prev) {
        tmp = node->value;
        if (search_in_history(av, tmp->cmd, env) == 1)
            break;
    }
    return env;
}
