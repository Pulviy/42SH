/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** interface
*/

#include "mysh.h"

data_node_t *read_history(history_t *history, char const *histfile)
{
    data_node_t *begin = NULL;
    data_node_t *node = NULL;
    FILE *file = fopen(histfile, "r");
    char *buffer = NULL;

    if (!file)
        return (NULL);
    while (readline(&buffer, file) > 0) {
        node = data_node_new(buffer);
        list_append((void **)&begin, node);
        history->hist_tail = node;
        free(buffer);
    }
    free(buffer);
    fclose(file);
    return (begin);
}

void write_history(shell_t *shell, char *line)
{
    data_node_t *node = NULL;

    if (!shell->history || shell->history->histfd == -1)
        return;
    node = data_node_new(line);
    list_append((void **)&shell->history->hist_list, node);
    shell->history->hist_tail = node;
    dprintf(shell->history->histfd, "%s\n", line);
}

char *get_next_history_token(shell_t *shell, char *begin)
{
    data_node_t *curr = shell->editor->histptr;

    if (!curr || !curr->next)
        return (NULL);
    if (shell->editor->histptr)
        curr = curr->next;
    if (!begin) {
        shell->editor->histptr = curr->next;
        return (shell->editor->histptr->data);
    }
    while (curr && strncmp(curr->data, begin, strlen(begin))) {
        curr = curr->next;
    }
    if (!curr)
        return (NULL);
    shell->editor->histptr = curr;
    return (shell->editor->histptr->data);
}

char *get_prev_history_token(shell_t *shell, char *begin)
{
    data_node_t *curr = shell->editor->histptr;

    if (!curr)
        curr = shell->history->hist_tail;
    if (!curr || !curr->prev)
        return (NULL);
    if (shell->editor->histptr)
        curr = curr->prev;
    if (!begin) {
        shell->editor->histptr = curr->prev;
        return (shell->editor->histptr->data);
    }
    while (curr && strncmp(curr->data, begin, strlen(begin))) {
        curr = curr->prev;
    }
    if (!curr)
        return (NULL);
    shell->editor->histptr = curr;
    return (shell->editor->histptr->data);
}