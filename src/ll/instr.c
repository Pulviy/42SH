/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** instr
*/

#include "mysh.h"

instr_t *instr_new(char *line)
{
    instr_t *instr = malloc(sizeof(instr_t));

    if (!instr)
        return (NULL);
    instr->next = NULL;
    instr->prev = NULL;
    instr->destroy = instr_destroy;
    instr->delim = 0;
    instr->is_or = 0;
    instr->is_and = 0;
    instr->is_pipe = 0;
    instr->is_bg = 0;
    instr->in = 0;
    instr->out = 1;
    parse_arguments(line, &instr->argv, &instr->argc);
    if (instr->argc <= 0) {
        instr_destroy(instr);
        instr = NULL;
    }
    return (instr);
}

void instr_destroy(void *instr)
{
    instr_t *td_instr = instr;

    if (!instr)
        return;
    arr_destroy(td_instr->argv);
    if (td_instr->in != 0)
        close(td_instr->in);
    if (td_instr->out != 1)
        close(td_instr->out);
    free(instr);
}
