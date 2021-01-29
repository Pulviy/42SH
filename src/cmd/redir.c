/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** redir
*/

#include "mysh.h"

void redirect_fds(shell_t *shell, int save[2])
{
    instr_t *instr = list_fetch_id((void **)&shell->cmd_heap, -1);

    if (instr->in != 0)
        dup2(instr->in, 0);
    else
        dup2(save[0], 0);
    if (count_pipes(shell) <= 1 && instr->out != 1)
        dup2(instr->out, 1);
    else
        dup2(save[1], 1);
}

void redirect_output(shell_t *shell, instr_t *instr, int is_double)
{
    int fd = 0;
    instr_t *out = instr->next;
    int open_flag = O_WRONLY | O_TRUNC | O_CREAT;

    if (!out || out->argc <= 0 || !out->argv[0][0]) {
        dprintf(2, "Missing name for redirect.\n");
        list_pop((void **)&shell->cmd_heap, instr);
        if (out)
            list_pop((void **)&shell->cmd_heap, out);
        return;
    }
    if (is_double)
        open_flag = O_WRONLY | O_APPEND | O_CREAT;
    fd = open(out->argv[out->argc - 1], open_flag, 0644);
    if (fd == -1) {
        dprintf(2, "%s: %s.\n", out->argv[out->argc - 1], strerror(errno));
        list_pop((void **)&shell->cmd_heap, instr);
    } else
        instr->out = fd;
    list_pop((void **)&shell->cmd_heap, out);
}

void double_redirect_input(shell_t *shell, instr_t *in)
{
    char **bufferptr = &shell->editor->buffer;
    int status = 0;
    int fds[2];

    if (in->argc <= 0 || !bufferptr || !*bufferptr || pipe(fds) == -1)
        return;
    while (status != -1 && strcmp(*bufferptr, *in->argv)) {
        status = editor_read(shell, "? ");
        if (status != -1 && strcmp(*bufferptr, *in->argv))
            dprintf(fds[1], "%s\n", *bufferptr);
    }
    close(fds[1]);
    dup2(fds[0], 0);
    close(fds[0]);
}

void redirect_input(shell_t *shell, instr_t *instr, int is_double)
{
    int fd = 0;
    instr_t *in = instr->next;

    if (!is_double && (!in || in->argc <= 0 || !in->argv[0][0])) {
        dprintf(2, "Missing name for redirect.\n");
        list_pop((void **)&shell->cmd_heap, instr);
        if (in)
            list_pop((void **)&shell->cmd_heap, in);
        return;
    }
    if (!is_double) {
        fd = open(in->argv[in->argc - 1], O_RDONLY);
        if (fd == -1) {
            dprintf(2, "%s: %s.\n", in->argv[in->argc - 1], strerror(errno));
            list_pop((void **)&shell->cmd_heap, instr);
        } else
            instr->in = fd;
    } else if (in)
        double_redirect_input(shell, in);
    list_pop((void **)&shell->cmd_heap, in);
}

void update_instr_io(shell_t *shell, instr_t *instr)
{
    instr->is_pipe = (instr->prev && instr->prev->delim == SINGLE_PIPE);
    instr->is_bg = (instr->delim == SINGLE_AMPER);
    instr->is_or = (instr->prev && instr->prev->delim == DOUBLE_PIPE);
    instr->is_and = (instr->prev && instr->prev->delim == DOUBLE_AMPER);
    if (instr->delim == SINGLE_LEFT || instr->delim == DOUBLE_LEFT)
        redirect_input(shell, instr, instr->delim == DOUBLE_LEFT);
    else if (instr->delim == SINGLE_RIGHT || instr->delim == DOUBLE_RIGHT)
        redirect_output(shell, instr, instr->delim == DOUBLE_RIGHT);
}