/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** locals
*/

#include "mysh.h"

#include <ctype.h>

void remove_existing(void **list, char *name)
{
    data_node_t *curr = NULL;
    int len = name ? strlen(name) : 0;

    if (!name || !list || !*list)
        return;
    while (list_poll(*list, (void **)&curr)) {
        if (curr->data[len] == '=' && !strncmp(curr->data, name, len)) {
            list_pop(list, curr);
            return;
        }
    }
}

void locals_new(shell_t *shell)
{
    char *arg = shell->cmd_heap->argv[1];
    int cut = -1;
    int i = 0;
    char new[1024] = {0};

    for (i = 0; arg[i]; ++i)
        cut = ((!arg[i + 1] && cut == -1) || arg[i] == '=') ? i : cut;
    strncpy(new, arg, cut + (arg[cut] != '='));
    for (i = 0; i < cut && i >= 0; ++i)
        i = (!isalnum(arg[i]) && arg[i] != '_') ? -2 : i;
    if (i <= 0) {
        dprintf(2, \
        "export: Variable name must contain alphanumeric characters.\n");
        shell->status = 1;
    } else {
        remove_existing((void **)&shell->locals, new);
        strcat(new, "=");
        strcat(new, arg + cut + 1);
        list_append((void **)&shell->locals, data_node_new(new));
    }
}

int builtin_export(shell_t *shell)
{
    if (strcmp(shell->cmd_heap->argv[0], "export"))
        return (0);
    shell->status = 0;
    if (shell->cmd_heap->argc <= 1) {
        list_print(shell->locals);
    } else if (shell->cmd_heap->argc > 2) {
        dprintf(2, "export: Too many arguments.\n");
        shell->status = 1;
    } else {
        locals_new(shell);
    }
    return (1);
}

int builtin_unset(shell_t *shell)
{
    if (strcmp(shell->cmd_heap->argv[0], "unset"))
        return (0);
    shell->status = 0;
    for (int i = 1; shell->cmd_heap->argv[i]; ++i)
        remove_existing((void **)&shell->locals, shell->cmd_heap->argv[i]);
    return (1);
}