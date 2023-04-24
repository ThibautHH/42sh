/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_history
*/

#include <stdlib.h>

#include "mysh.h"

env_t *builtin_history(UNUSED char **av, env_t *env)
{
    history_t *tmp;

    for (list_node_t *node = env->history->head; node != NULL;
    node = node->next) {
        tmp = node->value;
        ice_printf("%d  %s  %s\n", tmp->index, tmp->date, tmp->cmd);
    }
    return env;
}
