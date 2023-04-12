/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_argument.c
*/

#include <malloc.h>

#include "mysh.h"

int count_words(const char *buffer)
{
    int sum = (buffer[0] != ' ');

    if (!buffer[0])
        return 1;
    for (int i = 0 ; buffer[i + 1] ; i++)
        sum += IS_SPACE(buffer[i]) && !IS_SPACE(buffer[i + 1])
                && !IS_END(buffer[i + 1]);
    return MAX(sum, 1);
}

static int get_len(const char *buffer)
{
    int i = 0;
    int j;

    for (; IS_SPACE(buffer[i]) && !IS_END(buffer[i]) ; i++);
    for (j = i; !IS_SPACE(buffer[j]) && !IS_END(buffer[j]) ; j++);

    return j - i;
}

static char *get_word(char *buffer, int *index)
{
    int len = get_len(buffer + *index);
    char *word = malloc(len + 1);

    if (!word)
        return NULL;
    word[len] = '\0';
    for (; IS_SPACE(buffer[*index]) ; (*index)++);
    for (int i = 0 ; i < len ; i++, (*index)++)
        word[i] = buffer[*index];

    (*index)++;

    return word;
}

char **get_argument(char *buffer)
{
    int i = 0;
    int index = 0;
    int nb_word = count_words(buffer);
    char **words = malloc(sizeof(char *) * (nb_word + 1));

    if (!words)
        return NULL;
    for (; i < nb_word ; i++) {
        words[i] = get_word(buffer, &index);
        if (!words[i])
            return NULL;
    }
    words[nb_word] = NULL;
    if (!words[nb_word - 1][0])
        words[nb_word - 1] = NULL;
    return words;
}
