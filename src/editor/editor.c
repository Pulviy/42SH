/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** editor
*/

#include "mysh.h"

editor_t *editor_new(void)
{
    editor_t *editor = malloc(sizeof(editor_t));

    if (editor == NULL)
        return (NULL);
    editor->histptr = NULL;
    editor->buffsize = BUFFSIZE;
    editor->bufflen = 0;
    editor->buffer = calloc(editor->buffsize, sizeof(char));
    if (!editor->buffer) {
        free(editor);
        return (NULL);
    }
    editor->prefix_len = 0;
    editor->prompt = strdup("> ");
    editor->c_pos = 0;
    editor->completion = NULL;
    return (editor);
}

void completion_destroy(node_t **list)
{
    node_t *curr = list && *list ? (*list)->next : NULL;
    node_t *next = list && *list ? curr->next : NULL;

    if (!curr)
        return;
    while (next && curr != *list) {
        data_node_destroy(curr);
        curr = next;
        next = next->next;
    }
    data_node_destroy(*list);
    *list = NULL;
}

void editor_destroy(editor_t *editor)
{
    if (!editor)
        return;
    completion_destroy((node_t **)&editor->completion);
    free(editor->buffer);
    free(editor->prompt);
}

void editor_reset(editor_t *editor)
{
    if (!editor)
        return;
    memset(editor->buffer, 0, editor->buffsize);
    editor->c_pos = 0;
    editor->bufflen = 0;
}