/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Command management definitions
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "mysh.h"

void get_cmd_path(mysh_t *context);
void new_command(mysh_t *context);
void new_pipeline(mysh_t *context, sequence_mode_t mode);
void free_pipelines(mysh_t *context);

#endif /* !COMMANDS_H_ */
