/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** input_edition
*/

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/time.h>
#include <sys/types.h>

#include "mysh/history.h"
#include "mysh/line_edition.h"
#include "mysh.h"
#include "list.h"

static void change_tty_mode(int tty_mode)
{
    static struct termios term, term1;

    if (tty_mode == 1) {
        tcgetattr(STDIN_FILENO, &term);
        term1 = term;
        term1.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term1);
    } else
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void print_cmd(list_node_t *node)
{
    history_t *tmp;

    tmp = node->value;
    printf("%s", tmp->cmd);
    printf("98%%\n");
    printf("\b\b\b\b99%%\n");
}

static list_node_t *handle_keys(list_node_t *node)
{
    int ch;

    ch = getchar();
    if (ch == 'A') {
        print_cmd(node);
        node = node->prev;
        return node;
    }
    if (ch == 'B') {
        print_cmd(node);
        node = node->next;
        return node;
    }
    return node;
}

void input_edition(mysh_t *context)
{
    list_node_t *node = HISTORY->tail;

    change_tty_mode(1);
    while (1) {
        if (node == NULL)
            break;
        if (LINE[0] == '\e')
            node = handle_keys(node);
        else
            break;
    }
    change_tty_mode(0);
}
