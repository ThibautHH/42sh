/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Command management definitions
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "mysh.h"

typedef struct path_size_s {
    size_t pathsize;
    size_t dirlen;
} path_size_t;

bool get_cmd_path(mysh_t *context);
void new_command(mysh_t *context);
void new_pipeline(mysh_t *context, sequence_mode_t mode);
void free_pipelines(mysh_t *context);
void print_sigerror(mysh_t *context, int status);
void wait_for_cmd(mysh_t *context);
bool run_unforked_builtin(mysh_t *context);

void run(mysh_t *context);
void wait_for_cmd(mysh_t *context);

#endif /* !COMMANDS_H_ */
