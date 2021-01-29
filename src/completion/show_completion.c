/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** show_completion
*/

#include <sys/ioctl.h>
#include "mysh.h"

char *get_last_word(char *lineptr, char *separators)
{
    int i = lineptr ? strlen(lineptr) - 1: 0;
    int save = i;

    if (!lineptr)
        return (NULL);
    while (i >= 0 && (i == save || !strchr(separators, lineptr[i])))
        --i;
    return (lineptr + (i + 1));
}

void show_completion(data_node_t *nodes)
{
    data_node_t *curr = NULL;

    if (!nodes)
        return;
    dprintf(2, "\n");
    while (list_poll((void *)nodes, (void **)&curr))
        dprintf(2, "  %s\n", get_last_word(curr->data, "/$ \t"));
}