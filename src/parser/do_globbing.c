/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Globbing and unquoting/unescaping functions
*/

#include <errno.h>
#include <glob.h>
#include <string.h>
#include <stdio.h>
#include "mysh.h"
#include "mysh/parsing_functions.h"

static void unescape_arg(mysh_t *context, size_t i)
{
    char *ptmp = P, *stmp = S;
    for (P = (S = CMDARGS[i]); *P;)
        if (!unquote(context))
            P++;
    for (P = CMDARGS[i]; *P; P++)
        if (IS_CHAR_ESCAPED)
            strcpy(P - 1, P);
    for (P = CMDARGS[i]; *P; P++)
        if (*P == '\\' && P[1] == '\\' && P[2] != '\\')
            strcpy(P, P + 1);
    P = ptmp, S = stmp;
}

static int readerr(const char *path, int globerrno)
{
    perror(path);
    return (globerrno != EACCES);
}

static bool is_pattern(mysh_t *context)
{
    static const char specials[6] = "*?[{";
    char *ptmp = P, *stmp = S;
    bool result = false;

    S = CMDARGS[CMDARGC - 1];
    for (P = S; *P; P++)
        if (strchr(specials, *P) && !IS_CHAR_ESCAPED) {
            result = true; break;
        }
    P = ptmp, S = stmp;
    return result;
}

static bool handle_glob_result(mysh_t *context, glob_t *globbuf, int result)
{
    if (globbuf->gl_pathc == 1
        && !strcmp(globbuf->gl_pathv[0], CMDARGS[CMDARGC - 1])) {
        if (is_pattern(context) && SET_PARSE_ERR
            && (fprintf(stderr, "%s: No match.\n", CMDCMD) < 0))
            DIE;
        else
            unescape_arg(context, CMDARGC - 1);
        globfree(globbuf);
        return true;
    }
    if (result && result != GLOB_NOMATCH) {
        globfree(globbuf);
        DIE;
    }
    return false;
}

void do_globbing(mysh_t *context)
{
    glob_t globbuf = {0};
    size_t oldargc = CMDARGC - 1;
    int result = glob(CMDARGS[CMDARGC - 1], 0x1c10, readerr, &globbuf);

    if (handle_glob_result(context, &globbuf, result))
        return;
    if (globbuf.gl_pathc)
        free(CMDARGS[CMDARGC - 1]);
    for (size_t j = 1; j < globbuf.gl_pathc; j++)
        CMDARGC++;
    CMDARGS = realloc(CMDARGS, CMDARGSZ);
    for (size_t i = oldargc; i < CMDARGC; i++) {
        CMDARGS[i] = strdup(globbuf.gl_pathv[i - oldargc]);
        if (!CMDARGS[i]) DIE;
        unescape_arg(context, i);
    }
    globfree(&globbuf);
}
