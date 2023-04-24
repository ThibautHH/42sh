/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** mysh.h
*/

#ifndef MYSH_H
    #define MYSH_H

    #include <sys/queue.h>

    #include <stdbool.h>
    #include <stdio.h>
<<<<<<< HEAD
    #include <stdlib.h>
    #include <unistd.h>
=======
>>>>>>> c16914e (FEAT(<history>): add history builtin)

    #include "ice/macro.h"
    #include "ice/array.h"
    #include "ice/string.h"
    #include "ice/output.h"
    #include "ice/printf.h"
    #include "list.h"
    #include "list/struct.h"
    #include "ice/string.h"

    #include "mysh/history.h"
    #include "mysh/parsing.h"
    #include "mysh/env.h"

    #define IS_END(x) (((x) == '\0') || ((x) == '\n'))
    #define IS_SPACE(x) (((x) == ' ') || ((x) == '\t'))
    #define ISWS(x) (x) == '\v' || (x) == '\f' || (x) == '\r' || (x) == '\n'
    #define IS_WHITESPACE(x) ((x) == ' ' || (x) == '\t' || ISWS(x))
    #define SMCLN ;
    #define TQFSIT(v, f, t)   (v) = (t)
    #define TQFSCND2(v, f, t) ((t) = TAILQ_NEXT(v, f), 1)
    #define TQFSCND(v, h, f, t) (v) && TQFSCND2(v, f, t)SMCLN TQFSIT(v, f, t)
    #define TQFS(v, h, f, t) (v) = TAILQ_FIRST(h)SMCLN TQFSCND(v, h, f, t)
    #define	TAILQ_FOREACH_SAFE(v, h, f, t) for (TQFS(v, h, f, t))
typedef struct history_s {
    char *cmd;
    int index;
    char *date;
} history_t;

typedef struct env_s {
    char **env;
    int status;
    bool exit;
    int ch;
    list_t *history;
} env_t;

    #define GET_LINE (LEN = getline(&LINE, &LINESZ, stdin))
    #define LINE_ITERATION (prompt(context), free_pipelines(context), errno = 0)
    #define PPLMIS(t) (PIPELINE->mode == SEQ_##t)
    #define PPLCNDLMODES (PPLMIS(AND) && !STATUS) || (PPLMIS(OR) && STATUS)
    #define PIPELINE_SHOULD_RUN (PPLMIS(NONE) || PPLCNDLMODES)

    #define LINE (context->line)
    #define LINESZ (context->size)
    #define LEN (context->len)
    #define ENV (&(context->env))
    #define ENVQ (&(ENV)->head)
    #define ENVC (ENV->count)
    #define PIPEFDS (context->pipefds)
    #define STATUS (context->status)
    #define EXIT (context->exit)

    #define DIE die(context, 84)

    #define DW_STRLEN(s, l) (l > 0 ? l : ice_strlen(s))
    #define DWRITE(fd, s, l) if (write(fd, s, DW_STRLEN(s, l)) < 0)DIE
    #define WRITE(s, l) DWRITE(STDOUT_FILENO, s, l)
    #define TTY_WRITE(s, l) tty_write(context, s, l)

typedef struct mysh_s {
    env_head_t env;
    char *line;
    size_t size;
    ssize_t len;
    TAILQ_HEAD(, pipeline_s) pipelines;
    pipeline_t *current_pipeline;
    parsing_context_t parsing;
    int pipefds[2];
    uc_t status;
    bool exit;
    int ch;
    list_t *history;
} mysh_t;

void mysh(mysh_t *context, char **env);
void prompt(mysh_t *context);
void cleanup(mysh_t *context);
void run_pipeline(mysh_t *context);

static inline bool is_stdin_tty(mysh_t *context)
{
    int is_tty = isatty(STDIN_FILENO);

    if (is_tty < 0)
        DIE;
    return is_tty;
}

static inline void tty_write(mysh_t *context, const char *str, size_t len)
{
    if (!is_stdin_tty(context))
        return;
    WRITE(str, len);
}

#endif
/**
 * @brief Display the environment
 * @param env The environment
 * @return env The new environment
 */
env_t *builtin_env(UNUSED char **av, env_t *env);

/**
 * @brief Exit the shell
 * @param env The environment
 * @param av The arguments
 * @return env The new environment
 */
env_t *builtin_setenv(char **av, env_t *env);

/**
 * @brief Unset an environment variable
 * @param env The environment
 * @param buffer The buffer
 * @return env The new environment
 */
env_t *builtin_unsetenv(char **av, env_t *env);

/**
 * @brief Set an environment variable
 * @param path The path of the binary
 * @param env The environment
 * @param buffer The buffer
 * @return env The new environment
 */
bool execute_binary(char *path, char **av,  env_t *env);

/**
 * @brief Create a new environment
 * @param env The environment
 * @return char** The new environment
 */
char **malloc_env(char **env);

/**
 * @brief Fix the environment
 * @param env The environment
 * @return char** The new environment
 */
char **fix_env(char **env);

/**
 * @brief Get an environment variable
 * @param name The name of the variable
 * @param env The environment
 * @return char* The value of the variable
 */
char *get_env(char *name, env_t *env);

/**
 * @brief Set an environment variable
 * @param env The environment
 * @param name The name of the variable
 * @param value The value of the variable
 * @return char** The new environment
 */
char **set_env(env_t *env, char *name, char *value) ;

/**
 * @brief Unset an environment variable
 * @param env The environment
 * @param name The name of the variable
 * @return char** The new environment
 */
char **unset_env(char **env, char *name);

/**
 * @brief Display the environment
 * @param env The environment
 * @return bool True if write failed
 */
bool display_env(char **env);

/**
 * @brief Get the current working directory
 * @param env The environment
 * @return char* The current working directory
 */
void exit_env(env_t *env);

/**
 * @brief Get the current working directory
 * @param env The environment
 * @return char* The current working directory
 */
void display_error(env_t *env, const char *format, const char *str);

env_t *builtin_history(char **av, env_t *env);

void get_history_data(char *buffer, env_t *env, history_t *history);

env_t *event_history(char **av, env_t *env);

#endif /* !MYSH_H */
