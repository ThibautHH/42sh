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
    char date[6];
    int check;
} history_t;

void flag_c(mysh_t *context);
void history_event(mysh_t *context, int offset);
void get_history_data(char *buffer, mysh_t *context);
bool handle_history_event(mysh_t *context);
void realloc_line(mysh_t *context, char *line, int offset);
void free_history(history_t *node);

#endif
