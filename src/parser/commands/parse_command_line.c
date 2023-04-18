/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** parse_command_line.c
*/

#include "ice/string.h"

char **parse_command_line(char *str)
{
    return ice_strsplit(str, ";");
}
