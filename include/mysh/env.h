/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** env.h
*/

#ifndef INC_42SH_ENV_H
    #define INC_42SH_ENV_H

    #include "mysh.h"

    #include <sys/queue.h>

    #define ENVN(env) ((env) ? (env)->name : NULL)
    #define ENVV(env) ((env) ? (env)->value : NULL)

    #define GET_ENV(n) ({env_t *v = env_get(context, n);ENVV(v);})

typedef struct env_s {
    char *name;
    char name_buffer[256];
    char value[4096];
    TAILQ_ENTRY(env_s) entries;
} env_t;

typedef struct env_head_s {
    TAILQ_HEAD(, env_s) head;
    size_t count;
} env_head_t;

typedef struct mysh_s mysh_t;

void load_env(mysh_t *context, char **env);
void destroy_env(mysh_t *context);
char **dup_env(mysh_t *context);
env_t *env_get(mysh_t *context, char *name);
void env_add(mysh_t *context, char *var);
void env_remove(mysh_t *context, char *name);
void env_update(mysh_t *context, char *name, char *value);
void display_env(mysh_t *context);

#endif /* !INC_42SH_ENV_H */
