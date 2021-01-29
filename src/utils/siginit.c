/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** siginit
*/

#include "mysh.h"

void handler(int sig)
{
    if (sig == SIGSEGV)
        exit(0);
}

void sig_init(void)
{
    struct sigaction sa;

    signal(SIGINT, SIG_IGN);
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handler;
    sa.sa_flags = SA_NODEFER;
    sigaction(SIGSEGV, &sa, NULL);
}