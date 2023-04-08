/*
** EPITECH PROJECT, 2022
** list
** File description:
** list.h
*/

#ifndef LIST_H
    #define LIST_H

    #include <stdbool.h>

    #include "list/struct.h"

/**
 * @brief Create a list_t object
 * @return list_t* The list
 * @note The list must be destroyed with list_destroy
*/
list_t *list_create(void);

/**
 * @brief Get the size of the list
 * @param list The list
*/
void list_destroy(list_t *list);

/**
 * @brief Destroy the list and the node value
 * @param list The list
 * @param destroy_node The function to destroy the node
*/
void list_destroy_node(list_t *list, void(*destroy_node)(void *));

/**
 * @brief Add a value at the end of list
 * @param list The list
 * @param value The value to add
 * @return bool False if error
 * @note The value must be freed by the user
 */
bool list_add(list_t *list, void *value);

/**
 * @brief Add a node at the end of list
 * @param list The list
 * @param node The node to add
 * @return bool False if error
 * @note The node must be freed by the user
*/
bool list_add_node(list_t *list, list_node_t *node);

/**
 * @brief Remove the value at the index
 * @param list The list
 * @param index The index
 * @return void* The value
 * @note The value must be freed by the user
*/
void *list_remove(list_t *list, ull_t index);

/**
 * @brief Remove the node
 * @param list The list
 * @param node The node
 * @return void* The value
 * @note The value must be freed by the user
*/
void *list_remove_node(list_t *list, list_node_t *node);

/**
 * @brief Get the value at the index
 * @param list The list
 * @param index The index
 * @return void* The value
*/
void *list_get(list_t *list, ull_t index);

/**
 * @brief Pop the node at the index
 * @param list The list
 * @param index The index
 * @return list_node_t* The node
 * @note The node must be freed by the user
*/
list_node_t *list_pop(list_t *list, ull_t index);

/**
 * @brief Pop the node
 * @param list The list
 * @param node The node
 * @return list_node_t* The node
 * @note The node must be freed by the user
*/
list_node_t *list_pop_node(list_t *list, list_node_t *node);

/**
 * @brief Sort the list
 * @param list The list
 * @param cmp The compare function
*/
void list_sort(list_t *list, ull_t (*cmp)(void *, void *));

#endif /* !LIST_H */
