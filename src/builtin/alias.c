/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** alias
*/

#include "mysh.h"

data_node_t *fetch_alias_node(shell_t *shell, char *name)
{
    data_node_t *buffer = NULL;
    int len = (name ? strlen(name) : 0);

    while (name && list_poll(shell->aliases, (void **)&buffer))
        if (!strncmp(buffer->data, name, len) && buffer->data[len] == '=')
            return (buffer);
    return (NULL);
}

void alias_create(shell_t *shell)
{
    char alias[BUFFSIZE] = {0};
    char *name = shell->cmd_heap->argv[1];
    data_node_t *node = fetch_alias_node(shell, name);
    int index = 2;

    strcpy(alias, name);
    strcat(alias, "=");
    while (index < shell->cmd_heap->argc) {
        strcat(alias, shell->cmd_heap->argv[index]);
        if (index < shell->cmd_heap->argc - 1)
            strcat(alias, " ");
        ++index;
    }
    if (node) {
        if (node->data)
            free(node->data);
        node->data = strdup(alias);
    } else {
        node = data_node_new(alias);
        list_append((void **)&shell->aliases, node);
    }
}

int builtin_alias(shell_t *shell)
{
    char *value = NULL;

    if (strcmp(shell->cmd_heap->argv[0], "alias"))
        return (0);
    if (shell->cmd_heap->argc == 1) {
        list_print(shell->aliases);
    } else if (shell->cmd_heap->argc == 2) {
        value = fetch_alias(shell, shell->cmd_heap->argv[1]);
        if (value)
            dprintf(1, "%s\n", value);
    } else {
        alias_create(shell);
    }
    return (1);
}