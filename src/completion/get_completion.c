/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_completion
*/

#include "mysh.h"

int cmdline_split(char *lineptr, char **beggin, char **pattern);

void complete_from_dir(char *dir, char *pat, char *beggin, data_node_t **list)
{
    DIR *dd = opendir(dir);
    data_node_t *new = NULL;
    struct dirent *dirent = NULL;
    char tmp[256] = {'\0'};
    char line[512] = {'\0'};

    while (dd && (dirent = readdir(dd))) {
        memset(tmp, 0, sizeof(char) * 256);
        if (!pat || !strncmp(dirent->d_name, pat, strlen(pat)))
            strncpy(tmp, dirent->d_name, 256);
        if (tmp[0] && dirent->d_type == DT_DIR)
            tmp[strlen(tmp)] = '/';
        if (tmp[0] && strcmp(tmp, "../") && strcmp(tmp, "./")) {
            strcpy(line, beggin ? beggin : "\0");
            strcat(line, tmp);
            new = data_node_new(line);
            list_append((void **)list, new);
            new->next = *list;
        }
    }
    closedir(dd);
}

data_node_t *complete_from_envpath(shell_t *shell, char *pattern, char *beggin)
{
    char *dir = NULL;
    char path[512] = "/bin/";
    data_node_t *list = NULL;

    if (my_getenv(shell, "PATH") != NULL)
        strncpy(path, my_getenv(shell, "PATH"), 255);
    dir = strtok(path, ":");
    while (dir) {
        complete_from_dir(dir, pattern, beggin, &list);
        dir = strtok(NULL, ":");
    }
    return (list);
}

data_node_t *complete_from_envvar(shell_t *shell, char *pattern, char *beggin)
{
    data_node_t *list = NULL;
    data_node_t *curr = NULL;
    char varname[256] = {'\0'};
    char *line = NULL;
    int n = 0;

    while (list_poll(shell->env_list, (void **)&curr)) {
        if (!strncmp(pattern + 1, curr->data, strlen(pattern + 1))) {
            memset(varname, 0, sizeof(char) * 256);
            for (n = 0; curr->data[n] != '='; ++n);
            strncpy(varname, curr->data, n);
            n += beggin ? strlen(beggin) + 1 : 1;
            line = calloc(n + 1, sizeof(char));
            sprintf(line, "%s$%s", beggin ? beggin : "\0", varname);
            ((node_t *)list_append((void **)&list, data_node_new(line)))->next \
            = list;
            free(line);
        }
    }
    return (list);
}

data_node_t *complete_from_thisdir(char *endword, char *beggin)
{
    char *path = NULL;
    char *pattern = endword;
    char *new_beggin = beggin;
    data_node_t *ret = NULL;

    for (int i = strlen(endword); i >= 0 && !path; --i) {
        if (endword[i] == '/') {
            path = strndup(endword, i + 1);
            new_beggin = calloc(i + 2 + strlen(beggin), sizeof(char));
            strcpy(new_beggin, beggin);
            strcat(new_beggin, path);
            pattern = endword + i + 1;
        }
    }
    complete_from_dir(path ? path : "./", pattern, new_beggin, &ret);
    if (path) {
        free(path);
        free(new_beggin);
    }
    return (ret);
}

data_node_t *get_completion(shell_t *shell, char *lineptr)
{
    char *endword = NULL;
    char *beggin = NULL;
    data_node_t *ret = NULL;
    int check = 0;

    for (; strchr(" \t", *lineptr); ++lineptr) {
        if (*lineptr == 0)
            return (NULL);
    }
    check = cmdline_split(lineptr, &beggin, &endword);
    if (lineptr && endword[0] == '$')
        ret = complete_from_envvar(shell, endword, beggin);
    else if (strchr(endword, '/') || check)
        ret = complete_from_thisdir(endword, beggin);
    else
        ret = lineptr ? complete_from_envpath(shell, endword, beggin) : ret;
    if (!ret)
        ret = complete_from_thisdir(endword, beggin);
    free(beggin);
    return (ret);
}