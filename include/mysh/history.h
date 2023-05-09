/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history
*/

#ifndef HISTORY_H_
    #define HISTORY_H_

    #include "mysh.h"

typedef struct history_s {
    char *cmd;
    int index;
    char *date;
    int check;
} history_t;

    void flag_c(mysh_t *context);
    void get_history_data(char *buffer, mysh_t *context);

#endif
