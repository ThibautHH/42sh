/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** input_edition
*/

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "mysh.h"
#include "list.h"

char *input_edition(mysh_t *context)
{
    history_t *tmp;
    int ch;

    ch = getchar();
    if (ch == 'A')
        printf("aaaAAAAAAAAA");
    return LINE;
}
