/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias
*/



#ifndef ALIAS_H_
    #define ALIAS_H_

    #include "mysh.h"

    #define ALIAS (&(context->alias))
    #define ALIASQ (&(ALIAS)->head)

    #define ALIASNLEN 4096
    #define ALIASVLEN 32768

    #define FORBIDDEN "%s: Too dangerous to alias that.\n"

typedef struct alias_s {
    char name[ALIASNLEN];
    char value[ALIASVLEN];
    TAILQ_ENTRY(alias_s) entries;
} alias_t;

typedef struct alias_head_s {
    TAILQ_HEAD(, alias_s) head;
    size_t count;
} alias_head_t;

/**
 * @brief Free the inside of the alias_t struct
 *
 * @param context Main structure of mysh
 * @return void
 */
void destroy_alias(mysh_t *context);

/**
 * @brief Check if the alias name is OK
 *
 * @param alias The name of the wanted alias
 * @return bool true if a forbidden name is used
 */
bool is_alias_forbidden(char *alias);

/**
 * @brief Print the value of a given alias
 *
 * @param context Main structure of mysh
 * @param name name of the alias to print
 * @return bool return true everytime
 */
bool print_alias(mysh_t *context, char *name);

/**
 * @brief replace commands in the input line by their alias values
 *
 * @param context Main structure of mysh
 * @return bool return true everytime
 */
_Bool substitute_alias(mysh_t *context);

alias_t *search_for_alias(mysh_t *context, char *name);

#endif /* !ALIAS_H_ */
