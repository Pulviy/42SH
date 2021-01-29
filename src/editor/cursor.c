/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** cursor
*/

#include "mysh.h"

static void cursor_shift_buffer(editor_t *e, int shift)
{
    int index = 0;
    char tmp1 = 0;
    char tmp2 = 0;

    if (shift < 0) {
        index = e->c_pos + 1;
        while (index < e->bufflen && e->buffer[index]) {
            e->buffer[index - 1] = e->buffer[index];
            ++index;
        }
        e->buffer[index - 1] = 0;
    } else {
        index = e->c_pos;
        while (index < e->bufflen + 1 || tmp1 != 0) {
            tmp1 = tmp2;
            tmp2 = e->buffer[index];
            e->buffer[index] = tmp1;
            ++index;
        }
    }
}

void cursor_move(editor_t *e, int shift)
{
    if (shift > 0 && e->c_pos + shift <= e->bufflen)
        e->c_pos += shift;
    else if (shift < 0 && e->c_pos + shift >= 0)
        e->c_pos += shift;
}

void cursor_delete(editor_t *e, int nchars)
{
    while (e->c_pos > 0 && nchars > 0) {
        cursor_move(e, -1);
        cursor_shift_buffer(e, -1);
        e->bufflen--;
        --nchars;
    }
}

void cursor_insert_ch(editor_t *e, char c)
{
    if (e->bufflen >= e->buffsize)
        return;
    if (e->c_pos != e->bufflen)
        cursor_shift_buffer(e, +1);
    e->buffer[e->c_pos] = c;
    ++e->bufflen;
    ++e->c_pos;
}

void cursor_insert_str(editor_t *e, char *str)
{
    while (*str) {
        cursor_insert_ch(e, *str);
        ++str;
    }
}