/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** utils
*/

#include "mysh.h"

int list_size(node_t *begin)
{
    int size = 0;
    node_t *buffer = NULL;

    while (list_poll(begin, (void **)&buffer))
        ++size;
    return (size);
}

void list_print(data_node_t *begin)
{
    data_node_t *buffer = NULL;

    while (list_poll(begin, (void **)&buffer))
        dprintf(1, "%s\n", buffer->data);
}

char **list_to_array(data_node_t *begin)
{
    char **arr = NULL;
    data_node_t *buffer = NULL;
    int index = 0;

    if (!begin)
        return (NULL);
    arr = calloc(list_size((node_t *)begin) + 1, sizeof(char *));
    while (list_poll(begin, (void **)&buffer)) {
        arr[index] = buffer->data;
        ++index;
    }
    return (arr);
}

data_node_t *array_to_list(char **arr)
{
    data_node_t *begin = NULL;

    while (arr && *arr) {
        list_append((void **)&begin, data_node_new(*arr));
        ++arr;
    }
    return (begin);
}

void arr_destroy(char **arr)
{
    char **ptr = arr;

    if (!arr)
        return;
    while (*ptr) {
        free(*ptr);
        ++ptr;
    }
    free(arr);
}
