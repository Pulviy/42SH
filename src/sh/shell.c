/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** shell
*/

#include "mysh.h"

shell_t *shell_new(char **envc)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (!shell)
        return (NULL);
    shell->editor = editor_new();
    shell->history = history_new();
    shell->env_list = array_to_list(envc);
    shell->env_arr = list_to_array(shell->env_list);
    shell->aliases = source_shrc();
    shell->builtin_list = init_builtins_list();
    shell->status = 0;
    shell->running = 1;
    shell->cmd_heap = NULL;
    return (shell);
}

int shell_run(shell_t *shell)
{
    int save[2];

    save[0] = dup(0);
    save[1] = dup(1);
    while (shell->running) {
        dup2(save[0], 0);
        dup2(save[1], 1);
        if (editor_read(shell, NULL) != -1) {
            write_history(shell, shell->editor->buffer);
            parse_cmd(shell);
            exec_cmd_heap(shell);
        } else {
            dprintf(1, "exit\n");
            shell->running = 0;
        }
    }
    return (shell->status);
}

void shell_destroy(shell_t *shell)
{
    if (!shell)
        return;
    list_destroy((void **)&shell->env_list);
    free(shell->env_arr);
    list_destroy((void **)&shell->cmd_heap);
    history_destroy(shell->history);
    free(shell->history);
    editor_destroy(shell->editor);
    free(shell->editor);
    arr_destroy(shell->builtin_list);
    list_destroy((void **)&shell->aliases);
    free(shell);
}
