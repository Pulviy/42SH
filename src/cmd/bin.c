/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** bin
*/

#include "mysh.h"

static int file_exists(char const *filepath)
{
    struct stat stat_buffer;
    int stat_status = 0;

    stat_status = stat(filepath, &stat_buffer);
    return (stat_status == 0 && access(filepath, F_OK) != -1);
}

char *get_bin_path(char *dir, char const *binname)
{
    char *binpath = NULL;
    size_t dir_len = (dir ? strlen(dir) : 0);
    size_t bin_len = (dir ? strlen(binname) : 0);
    char last_char = dir[dir_len - 1];
    size_t path_len = dir_len + (last_char != '/') + bin_len;

    binpath = calloc(path_len + 1, sizeof(char));
    if (last_char != '/')
        sprintf(binpath, "%s/%s", dir, binname);
    else
        sprintf(binpath, "%s%s", dir, binname);
    if (!file_exists(binpath)) {
        perror(binpath);
        free(binpath);
        return (NULL);
    }
    return (binpath);
}

int is_in_dir(char const *name, char *dirname)
{
    DIR *dir = NULL;
    dirent_t *ent = NULL;
    int found = 0;

    if (file_exists(dirname))
        dir = opendir(dirname);
    while (!found && dir && (ent = readdir(dir)))
        if (name && strcmp(name, ent->d_name) == 0)
            found = 1;
    closedir(dir);
    return (found);
}

char *locate_bin(shell_t *shell, char const *name)
{
    char *dir = NULL;
    char *binpath = NULL;
    char path[BUFFSIZE] = "/bin/";
    char *var = my_getenv(shell, "PATH");

    if (!name)
        return (NULL);
    if (var != NULL)
        strncpy(path, var, 255);
    if (strchr(name, '/'))
        return (file_exists(name) ? strdup(name) : NULL);
    dir = strtok(path, ":");
    while (name && dir && !binpath) {
        if (is_in_dir(name, dir)) {
            binpath = get_bin_path(dir, name);
            shell->status = (binpath == NULL);
        }
        dir = strtok(NULL, ":");
    }
    return (binpath);
}
