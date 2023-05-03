/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history
*/

#ifndef HISTORY_H_
    #define HISTORY_H_

    #include "mysh.h"
    #include "mysh/env.h"

typedef struct history_s {
    char *cmd;
    int index;
    char *date;
    int check;
} history_t;

bool event_history(char **av, mysh_t *env);

/**
 * @brief Print the command history
 *
 * @param av The arguments
 * @param env The structure env
 * @return bool, true if no error, false if error
 */
bool builtin_history(char **av, mysh_t *env);
void get_history_data(char *buffer, mysh_t *context);
void flag_c(mysh_t *context);
void handle_error_msg(char *str);

#endif
