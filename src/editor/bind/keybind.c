/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** keybind
*/

#include "mysh.h"

int exec_bind_tab(shell_t *shell, char key)
{
    editor_t *e = shell->editor;
    data_node_t *curr = NULL;
    int check = 0;
    int len = strlen(e->buffer);

    if (!(key == TAB))
        return (0);
    while (check == 0 && list_poll((void *)e->completion, (void **)&curr))
        check = (strncmp(e->buffer, curr->data, len) == 0);
    if (check == 0) {
        completion_destroy((node_t **)&e->completion);
        e->completion = get_completion(shell, e->buffer);
        show_completion(e->completion);
    } else {
        editor_reset(e);
        cursor_insert_str(e, e->completion->data);
        e->completion = e->completion->next;
        if (list_size((node_t *)e->completion) <= 1)
            completion_destroy((node_t **)&e->completion);
    }
    return (1);
}

int exec_bind_delete(editor_t *e, char key)
{
    if (!(key == BACKSPACE) && !(key == DEL))
        return (0);
    completion_destroy((node_t **)&e->completion);
    if ((key == BACKSPACE))
        cursor_delete(e, 1);
    else if ((key == DEL) && e->c_pos < e->bufflen) {
        cursor_move(e, 1);
        cursor_delete(e, 1);
    }
    return (1);
}

int exec_special_key_bindings(shell_t *shell, char key)
{
    editor_t *e = shell->editor;
    char c = 0;

    if (key != 27 || read(0, &c, 1) == -1 || !strchr("ABCD13", c))
        return (c);
    if (c == '1' && read(0, &c, 1) != -1 && read(0, &c, 1) != -1) {
        if (read(0, &c, 1) == -1 || !strchr("ABCD", c))
            return (c);
        exec_bind_ctrl_up_down_arrows(e, c);
        exec_bind_ctrl_left_right_arrows(e, c);
    } else if (c == '3' && read(0, &c, 1) != -1 && c == DEL) {
        exec_bind_delete(e, c);
    } else {
        exec_bind_up_down_arrows(shell, c);
        exec_bind_left_right_arrows(e, c);
    }
    return (c);
}

int exec_escape_key_bindings(shell_t *shell, char key)
{
    char c = 0;
    editor_t *e = shell->editor;

    if (key != 27 || read(0, &c, 1) == -1 || !strchr("D[\177", c))
        return (c);
    if (c == 'D')
        exec_bind_ctrl_del(e, c);
    else if (c == BACKSPACE)
        exec_bind_ctrl_del(e, CTRL_BKSP);
    else
        exec_special_key_bindings(shell, key);
    return (1);
}

int exec_key_bindings(shell_t *shell, char key)
{
    int is_exec = 0;
    editor_t *e = shell->editor;

    if (key == ENTER && e->completion)
        completion_destroy((node_t **)&e->completion);
    else if (key == ENTER)
        return (0);
    if (key == ESCAPE)
        return (exec_escape_key_bindings(shell, key));
    is_exec = (!is_exec ? exec_bind_delete(e, key) : is_exec);
    is_exec = (!is_exec ? exec_bind_ctrl_del(e, key) : is_exec);
    is_exec = (!is_exec ? exec_bind_tab(shell, key) : is_exec);
    is_exec = (!is_exec ? exec_bind_ctrl_z(e, key) : is_exec);
    is_exec = (!is_exec ? exec_bind_ctrl_a(e, key) : is_exec);
    is_exec = (!is_exec ? exec_bind_ctrl_c(e, key) : is_exec);
    is_exec = (!is_exec ? key < 32 : is_exec);
    if (!is_exec)
        completion_destroy((node_t **)&e->completion);
    return (is_exec);
}