/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** list
*/

#include "mysh.h"

void *list_append(void **begin, void *node)
{
    node_t **td_begin = (node_t **)begin;
    node_t *td_node = (node_t *)node;
    node_t *tmp = *td_begin;

    if (!node)
        return (NULL);
    if (!tmp) {
        *begin = node;
    } else {
        while (tmp && tmp->next && tmp->next != *begin)
            tmp = tmp->next;
        tmp->next = node;
    }
    td_node->prev = tmp;
    td_node->next = NULL;
    return (node);
}

void list_pop(void **begin, void *node)
{
    node_t **td_begin = (node_t **)begin;
    node_t *td_node = (node_t *)node;

    if (!td_node->prev) {
        *begin = (node_t *)td_node->next;
        if (*td_begin)
            (*td_begin)->prev = NULL;
    } else {
        ((node_t *)td_node->prev)->next = td_node->next;
    }
    td_node->destroy(node);
}

void *list_fetch_id(void **begin, int id)
{
    node_t *tmp = (node_t *)*begin;

    while (tmp && tmp->next && (id > 0 || id == -1)) {
        tmp = tmp->next;
        id -= (id != -1);
    }
    if (tmp && (id >= 0 || id == -1))
        return (tmp);
    else
        return (NULL);
}

int list_poll(void *begin, void **buffer)
{
    node_t **td_buffer = (node_t **)buffer;

    if (begin && !*buffer)
        *buffer = begin;
    else if (begin && (*td_buffer)->next && (*td_buffer)->next != begin)
        *buffer = (*td_buffer)->next;
    else
        return (0);
    return (1);
}

void list_destroy(void **begin)
{
    node_t **td_begin = (node_t **)begin;

    while (*td_begin)
        list_pop(begin, *begin);
    *begin = NULL;
}