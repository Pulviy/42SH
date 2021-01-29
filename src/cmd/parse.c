/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** parse
*/

#include "mysh.h"

int str_match_delim(char *str, char *delims[])
{
    int index = 0;

    while (str && delims[index]) {
        if (strncmp(str, delims[index], strlen(delims[index])) == 0)
            return (index);
        ++index;
    }
    return (-1);
}

int get_next_instr(char **begin, char **end, int *delim)
{
    char quote = 0;
    int inhibitor = 0;
    static char *del[] = {";", "<<", "<", ">>", ">", "||", "|", "&&", "&", 0};

    if (!*begin || !**begin)
        return (0);
    *end = *begin;
    *delim = (!quote && !inhibitor ? str_match_delim(*end, del) : -1);
    while (**end && *delim == -1) {
        if (!inhibitor && (**end == '\'' || **end == '\"'))
            quote = (quote == **end ? 0 : (quote == 0 ? **end : quote));
        inhibitor = (!inhibitor && **end == '\\');
        ++*end;
        *delim = (!quote && !inhibitor ? str_match_delim(*end, del) : -1);
    }
    if (!**end)
        return (quote ? quote : 1);
    **end = 0;
    *end += (*delim != -1 && del[*delim] ? strlen(del[*delim]) : 0);
    return (quote ? quote : *delim != -1);
}

void shell_add_cmd(shell_t *shell, char *cmd, cmd_delim_t delim)
{
    char buffer[BUFFSIZE] = {0};
    instr_t *instr = NULL;

    strcpy(buffer, cmd);
    replace_alias(shell, buffer);
    parse_envvar(shell, buffer);
    instr = instr_new(buffer);
    if (!instr)
        return;
    instr->delim = delim;
    list_append((void **)&(shell->cmd_heap), instr);
}

void parse_cmd(shell_t *shell)
{
    char *begin = shell->editor->buffer;
    char *end = NULL;
    int delim = 0;
    instr_t *instr = NULL;
    int status = 0;

    status = get_next_instr(&begin, &end, &delim);
    while (status == 1) {
        shell_add_cmd(shell, begin, delim);
        begin = end;
        status = get_next_instr(&begin, &end, &delim);
    }
    if (status != 0) {
        dprintf(2, "Unmatched '%c'.\n", status);
        list_destroy((void **)&(shell->cmd_heap));
        shell->status = 1;
    }
    while (list_poll(shell->cmd_heap, (void **)&instr))
        update_instr_io(shell, instr);
}