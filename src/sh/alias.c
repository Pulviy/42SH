/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parse_shrc
*/

#include "mysh.h"
#include <ctype.h>

void get_next_word(char **curr, char **next)
{
    while (**curr && **curr <= 32)
        ++*curr;
    *next = *curr;
    while (**next && **next > 32)
        ++*next;
    while (**next && **next <= 32) {
        **next = 0;
        ++*next;
    }
}

data_node_t *parse_alias(char *lineptr)
{
    char *curr = lineptr;
    char *next = NULL;
    char data[BUFFSIZE] = {0};

    get_next_word(&curr, &next);
    sprintf(data, "%s=%s", curr, next);
    return (data_node_new(data));
}

data_node_t *source_shrc(void)
{
    FILE *shrc = fopen(SHRC_LOC, "r");
    data_node_t *begin = NULL;
    data_node_t *node = NULL;
    char *line = NULL;
    char *curr = NULL;
    char *next = NULL;

    if (!shrc)
        return (NULL);
    while (readline(&line, shrc) > 0) {
        curr = line;
        get_next_word(&curr, &next);
        if (strcmp(curr, "alias") == 0) {
            node = parse_alias(next);
            list_append((void **)&begin, node);
        }
        free(line);
    }
    free(line);
    fclose(shrc);
    return (begin);
}

char *fetch_alias(shell_t *shell, char *name)
{
    data_node_t *buffer = NULL;
    int len = strlen(name);
    char *value = NULL;

    while (name && !value && list_poll(shell->aliases, (void **)&buffer)) {
        if (!strncmp(buffer->data, name, len) && buffer->data[len] == '=')
            value = &buffer->data[len + 1];
    }
    return (value);
}

void replace_alias(shell_t *shell, char *line)
{
    char cpy[BUFFSIZE] = {0};
    char *name = cpy;
    char *end = NULL;
    char *alias = NULL;

    strcpy(cpy, line);
    get_next_word(&name, &end);
    alias = fetch_alias(shell, name);
    if (!alias)
        return;
    sprintf(line, "%s %s", alias, end);
}