/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** env
*/

#include "mysh.h"

data_node_t *my_getenv_node(shell_t *shell, char const *name)
{
    data_node_t *buffer = NULL;
    size_t len = (name ? strlen(name) : 0);

    while (list_poll(shell->env_list, (void **)&buffer)) {
        if (!strncmp(buffer->data, name, len) && buffer->data[len] == '=')
            return (buffer);
    }
    return (NULL);
}

char *my_getenv(shell_t *shell, char const *name)
{
    data_node_t *buffer = NULL;
    size_t len = (name ? strlen(name) : 0);

    if (!name)
        return (NULL);
    while (list_poll(shell->env_list, (void **)&buffer)) {
        if (!strncmp(buffer->data, name, len) && buffer->data[len] == '=')
            return (&buffer->data[len + 1]);
    }
    return (NULL);
}

data_node_t *my_setenv(shell_t *shell, char const *name, char const *value)
{
    data_node_t *node = NULL;
    size_t name_len = (name ? strlen(name) : 0);
    size_t value_len = (value ? strlen(value) : 0);
    char *string = calloc(name_len + value_len + 2, sizeof(char));

    if (!name)
        return (NULL);
    sprintf(string, "%s=%s", (name ? name : ""), (value ? value : ""));
    node = my_getenv_node(shell, name);
    if (!node) {
        node = list_append((void **)&shell->env_list, data_node_new(string));
        free(string);
    } else {
        if (node->data)
            free(node->data);
        node->data = string;
    }
    shell->status = 0;
    update_env_arr(shell);
    return (node);
}

void my_unsetenv(shell_t *shell, char const *name)
{
    data_node_t *node = NULL;

    if (!name)
        return;
    node = my_getenv_node(shell, name);
    if (node)
        list_pop((void **)&shell->env_list, node);
    update_env_arr(shell);
}

void update_env_arr(shell_t *shell)
{
    free(shell->env_arr);
    shell->env_arr = list_to_array(shell->env_list);
}