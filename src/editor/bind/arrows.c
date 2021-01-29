/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** arrows
*/

#include "mysh.h"
#include <ctype.h>

int exec_bind_up_down_arrows(shell_t *shell, char key)
{
    editor_t *e = shell->editor;
    char *token = NULL;
    static char save[BUFFSIZE] = {0};

    if (!(key == ARROW_UP) && !(key == ARROW_DOWN))
        return (0);
    if (!e->histptr) {
        strcpy(save, shell->editor->buffer);
        save[strlen(shell->editor->buffer)] = 0;
    }
    if (key == ARROW_UP)
        token = get_prev_history_token(shell, save);
    else if (key == ARROW_DOWN)
        token = get_next_history_token(shell, save);
    editor_reset(e);
    if (!token)
        cursor_insert_str(shell->editor, save);
    else
        cursor_insert_str(shell->editor, token);
    return (1);
}

int exec_bind_left_right_arrows(editor_t *e, char key)
{
    if (!(key == ARROW_LEFT) && !(key == ARROW_RIGHT))
        return (0);
    if ((key == ARROW_LEFT))
        cursor_move(e, -1);
    else if ((key == ARROW_RIGHT))
        cursor_move(e, +1);
    return (1);
}

int exec_bind_ctrl_up_down_arrows(editor_t *e, char key)
{
    if (!(key == ARROW_UP) && !(key == ARROW_DOWN))
        return (0);
    e = e;
    return (1);
}

int exec_bind_ctrl_left_right_arrows(editor_t *e, char key)
{
    if (!(key == ARROW_LEFT) && !(key == ARROW_RIGHT))
        return (0);
    if (key == ARROW_LEFT) {
        while (e->c_pos > 0 && !isalnum(e->buffer[e->c_pos - 1]))
            cursor_move(e, -1);
        while (e->c_pos > 0 && isalnum(e->buffer[e->c_pos - 1]))
            cursor_move(e, -1);
    } else {
        while (e->c_pos < e->bufflen && isalnum(e->buffer[e->c_pos]))
            cursor_move(e, +1);
        if (e->c_pos > 0 && !isalnum(e->buffer[e->c_pos - 1]))
            cursor_move(e, +1);
        while (e->c_pos < e->bufflen && !isalnum(e->buffer[e->c_pos]))
            cursor_move(e, +1);
    }
    return (1);
}