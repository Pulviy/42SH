/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** prompt
*/

#include "mysh.h"

int normal_prompt(editor_t *editor, char *custom_prompt)
{
    char *prompt = (custom_prompt ? custom_prompt : editor->prompt);
    char c = 0;
    size_t readsize = 1;

    dprintf(1, prompt);
    while ((int)readsize >= 0) {
        readsize = read(0, &c, 1);
        if ((int)readsize <= 0)
            return (-1);
        else if (c == '\n')
            return (0);
        else
            cursor_insert_ch(editor, c);
    }
    return (0);
}

int editor_prompt(shell_t *shell, char *custom_prompt)
{
    editor_t *editor = shell->editor;
    char *prompt = (custom_prompt ? custom_prompt : editor->prompt);
    int c_pos = editor->prefix_len + editor->c_pos + strlen(prompt);
    int pref = editor->prefix_len;
    char *buffer = editor->buffer;
    char c = 0;

    dprintf(1, "\r\033[%dC\033[K%s%s\r\033[%dC", pref, prompt, buffer, c_pos);
    if (read(0, &c, 1) == -1 || c == CTRL_D)
        return (-1);
    if (exec_key_bindings(shell, c))
        return (editor_prompt(shell, custom_prompt));
    return (c);
}

int editor_read(shell_t *shell, char *prompt)
{
    editor_t *editor = shell->editor;
    char c = 0;

    editor_reset(shell->editor);
    if (!(enable_raw_terminal() && getcpos(&shell->editor->prefix_len, 0)))
        return (normal_prompt(editor, prompt));
    while (editor->c_pos < editor->buffsize && c != ENTER) {
        c = editor_prompt(shell, prompt);
        if (c == -1) {
            disable_raw_terminal();
            return (-1);
        } else if (c == ENTER) {
            completion_destroy((node_t **)&editor->completion);
            dprintf(1, "\n");
        } else {
            cursor_insert_ch(editor, c);
        }
    }
    shell->editor->histptr = NULL;
    disable_raw_terminal();
    return (0);
}