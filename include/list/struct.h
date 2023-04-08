/*
** EPITECH PROJECT, 2022
** list
** File description:
** list/struct.h
*/

#ifndef LIST_STRUCT_H
    #define LIST_STRUCT_H

    #include "ice/types.h"

typedef struct list_node_s {
    void *value;
    struct list_node_s *next;
    struct list_node_s *prev;
} list_node_t;

typedef struct list_s {
    list_node_t *head;
    list_node_t *tail;
    ull_t size;
} list_t;

#endif /* !LIST_STRUCT_H */
