/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** var.h
*/

#ifndef VAR_H
    #define VAR_H

    #include "mysh.h"

    #include <sys/queue.h>

    #define VARNLEN 256
    #define VARVLEN 4096
    #define VARN(env) ((env) ? (env)->name : NULL)
    #define VARV(env) ((env) ? ((env)->buffer + VARNLEN) : NULL)

    #define GET_VAR(n, t) ({var_t *v = var_get(context, n, VAR_##t);VARV(v);})

typedef enum {
    VAR_ENV,
    VAR_SHELL
} var_type_t;

typedef struct var_s {
    char *name;
    char buffer[VARNLEN + VARVLEN];
    TAILQ_ENTRY(var_s) entries;
} var_t;

typedef struct var_head_s {
    TAILQ_HEAD(, var_s) head;
    size_t count;
} var_head_t;

typedef struct mysh_s mysh_t;

void load_env(mysh_t *context, char **env);
void destroy_vars(mysh_t *context, var_type_t type);
char **dup_env(mysh_t *context);
var_t *var_get(mysh_t *context, char *name, var_type_t type);
void var_add(mysh_t *context, char *var, var_type_t type);
void var_remove(mysh_t *context, char *name, var_type_t type);
void var_update(mysh_t *context, char *name, char *value, var_type_t type);
bool is_var_named(var_t *var, char *name);

#endif /* !VAR_H */
