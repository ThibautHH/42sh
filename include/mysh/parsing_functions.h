/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Parsing function definitions
*/

#ifndef PARSING_FUNCTIONS_H_
    #define PARSING_FUNCTIONS_H_

    #include "mysh.h"

bool is_char_escaped(mysh_t *context);
void get_ppl_separator(mysh_t *context);
void to_next_token(mysh_t *context);
bool unquote(mysh_t *context);
void to_token_end(mysh_t *context);

#endif /* !PARSING_FUNCTIONS_H_ */
