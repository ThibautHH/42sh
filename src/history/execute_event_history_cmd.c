/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** execute_event_history_cmd
*/

#include "mysh/commands.h"
#include "mysh.h"

void execute_event_history_cmd(mysh_t *context, char *str)
{
    mysh_t context2 = *context;

    context2.line = str;
    parse_command_line(&context2);
    TAILQ_FOREACH(context2.current_pipeline, &context2.pipelines, entries)
        run_pipeline(&context2);
    free_pipelines(&context2);
}
