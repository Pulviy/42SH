/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** ctrl
*/

#include "mysh.h"
#include <ctype.h>

int exec_bind_ctrl_del(editor_t *e, char key)
{
    if (!(key == 'D') && !(key == CTRL_BKSP))
        return (0);
    completion_destroy((node_t **)&e->completion);
    if (key == 'D') {
        while (e->c_pos < e->bufflen && !isalnum(e->buffer[e->c_pos])) {
            cursor_move(e, 1);
            cursor_delete(e, 1);
        }
        while (e->c_pos < e->bufflen && isalnum(e->buffer[e->c_pos])) {
            cursor_move(e, 1);
            cursor_delete(e, 1);
        }
    } else {
        while (e->c_pos > 0 && !isalnum(e->buffer[e->c_pos - 1]))
            cursor_delete(e, 1);
        while (e->c_pos > 0 && isalnum(e->buffer[e->c_pos - 1]))
            cursor_delete(e, 1);
    }
    return (1);
}

int exec_bind_ctrl_z(editor_t *e, char key)
{
    if (!(key == CTRL_Z))
        return (0);
    e = e;
    return (1);
}

int exec_bind_ctrl_c(editor_t *e, char key)
{
    if (!(key == CTRL_C))
        return (0);
    dprintf(1, "\n");
    editor_reset(e);
    return (1);
}

int exec_bind_ctrl_a(editor_t *e, char key)
{
    if (!(key == CTRL_A))
        return (0);
    e->c_pos = 0;
    return (1);
}