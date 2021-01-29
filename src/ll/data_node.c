/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** data_node_t
*/

#include "mysh.h"

data_node_t *data_node_new(char *data)
{
    data_node_t *node = malloc(sizeof(data_node_t));

    if (!node)
        return (NULL);
    node->prev = NULL;
    node->next = NULL;
    node->destroy = data_node_destroy;
    node->data = strdup(data);
    return (node);
}

void data_node_destroy(void *node)
{
    data_node_t *td_node = node;

    if (!node)
        return;
    if (td_node->data)
        free(td_node->data);
    free(node);
}