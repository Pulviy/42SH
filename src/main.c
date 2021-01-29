/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** main
*/

#include "mysh.h"

void sig_init(void);

static shell_t **get_shell(void)
{
    static shell_t *shell = NULL;

    return (&shell);
}

static shell_t *init_shell(char *envp[])
{
    shell_t **shell = get_shell();

    if (*shell)
        return (*shell);
    *shell = shell_new(envp);
    return (*shell);
}

static void exit_shell(void)
{
    shell_t **shell = get_shell();

    if (!*shell)
        return;
    shell_destroy(*shell);
}

int main(int argc, char *argv[], char *envp[])
{
    shell_t *shell = NULL;
    int status = 0;


    if (argc == 2 && !strcmp(argv[1], "-h")) {
        put_usage();
    } else {
        sig_init();
        atexit(exit_shell);
        shell = init_shell(envp);
        status = shell_run(shell);
    }
    return (status);
}