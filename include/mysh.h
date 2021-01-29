/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** mysh
*/

#ifndef MYSH_H_
#define MYSH_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct dirent dirent_t;
typedef struct shell_s shell_t;
typedef struct editor_s editor_t;
typedef struct history_s history_t;
typedef struct instr_s instr_t;
typedef struct jobs_s jobs_t;
typedef struct node_s node_t;
typedef struct data_node_s data_node_t;
typedef enum cmd_delim_e cmd_delim_t;

#define BUFFSIZE (4096)
#define HIST_LOC ("./conf/.42sh_history")
#define SHRC_LOC ("./conf/.42shrc")

/*
*  LL
*/

struct node_s {
    void *next;
    void *prev;
    void (*destroy)(void *);
};

struct data_node_s {
    void *next;
    void *prev;
    void (*destroy)(void *);
    char *data;
};

struct instr_s {
    instr_t *next;
    instr_t *prev;
    void (*destroy)(void *);
    int delim;
    int is_and;
    int is_or;
    int is_pipe;
    int is_bg;
    int in;
    int out;
    char **argv;
    int argc;
};

instr_t *instr_new(char *line);
void instr_destroy(void *instr);
data_node_t *data_node_new(char *data);
void data_node_destroy(void *node);
void *list_append(void **begin, void *node);
void list_pop(void **begin, void *node);
void *list_fetch_id(void **begin, int id);
int list_poll(void *begin, void **buffer);
void list_destroy(void **begin);
int list_size(node_t *begin);
void list_print(data_node_t *begin);

/*
**  UTILS
*/
int put_usage(void);
char **list_to_array(data_node_t *begin);
data_node_t *array_to_list(char **arr);
void arr_destroy(char **arr);
ssize_t readline(char **buffer, FILE *stream);
int is_file(char *path);
char *get_last_word(char *lineptr, char *separators);
int is_file_elf(char *file);
void strn_shift(char *str, int n);
int getcpos(int *x, int *y);

/*
**  ENVIRONMENT
*/
char *my_getenv(shell_t *shell, char const *name);
data_node_t *my_getenv_node(shell_t *shell, char const *name);
data_node_t *my_setenv(shell_t *shell, char const *name, char const *value);
void my_unsetenv(shell_t *shell, char const *name);
void update_env_arr(shell_t *shell);

/*
**  SHELL
*/
struct shell_s {
    history_t *history;
    editor_t *editor;
    jobs_t *jobs;
    data_node_t *env_list;
    data_node_t *locals;
    char **env_arr;
    char **builtin_list;
    data_node_t *aliases;
    instr_t *cmd_heap;
    int running;
    int status;
};

shell_t *shell_new(char **envc);
void shell_destroy(shell_t *shell);
int shell_run(shell_t *shell);

/*
**  EDITOR
*/
typedef enum cmd_keys_e {
    CTRL_A      =   1,
    CTRL_C      =   3,
    CTRL_D      =   4,
    TAB         =   9,
    ENTER       =   13,
    CTRL_BKSP   =   23,
    CTRL_Z      =   26,
    ESCAPE      =   27,
    ARROW_UP    =   65,
    ARROW_DOWN  =   66,
    ARROW_RIGHT =   67,
    ARROW_LEFT  =   68,
    DEL         =   126,
    BACKSPACE   =   127,
} cmd_keys_t;

struct editor_s {
    int buffsize;
    int prefix_len;
    int c_pos;
    int bufflen;
    char *buffer;
    char *prompt;
    data_node_t *histptr;
    data_node_t *completion;
};

editor_t *editor_new(void);
void editor_destroy(editor_t *editor);
void editor_reset(editor_t *editor);
int editor_read(shell_t *shell, char *prompt);
int enable_raw_terminal(void);
void disable_raw_terminal(void);
int exec_key_bindings(shell_t *shell, char key);
int exec_escape_key_bindings(shell_t *shell, char key);
int exec_special_key_bindings(shell_t *shell, char key);
void cursor_move(editor_t *e, int direction);
void cursor_delete(editor_t *e, int nchars);
void cursor_insert_ch(editor_t *e, char c);
void cursor_insert_str(editor_t *e, char *str);
data_node_t *get_completion(shell_t *shell, char *lineptr);
void show_completion(data_node_t *nodes);
void completion_destroy(node_t **list);

// KEY BINDING
int exec_bind_up_down_arrows(shell_t *shell, char key);
int exec_bind_ctrl_up_down_arrows(editor_t *e, char key);
int exec_bind_left_right_arrows(editor_t *e, char key);
int exec_bind_ctrl_left_right_arrows(editor_t *e, char key);
int exec_bind_tab(shell_t *shell, char key);
int exec_bind_delete(editor_t *e, char key);
int exec_bind_ctrl_del(editor_t *e, char key);
int exec_bind_ctrl_z(editor_t *e, char key);
int exec_bind_ctrl_c(editor_t *e, char key);
int exec_bind_ctrl_a(editor_t *e, char key);

/*
**  HISTORY
*/
struct history_s {
    int histfd;
    data_node_t *hist_list;
    data_node_t *hist_tail;
};

history_t *history_new(void);
void history_destroy(history_t *history);
char *get_next_history_token(shell_t *shell, char *begin);
char *get_prev_history_token(shell_t *shell, char *begin);
data_node_t *read_history(history_t *history, char const *histfile);
void write_history(shell_t *shell, char *line);

/*
**  CMDS
*/
enum cmd_delim_e {
    SEMICOLON,
    DOUBLE_LEFT,
    SINGLE_LEFT,
    DOUBLE_RIGHT,
    SINGLE_RIGHT,
    DOUBLE_PIPE,
    SINGLE_PIPE,
    DOUBLE_AMPER,
    SINGLE_AMPER
};

char **init_builtins_list(void);
int is_in_dir(char const *name, char *dirname);
char *get_bin_path(char *dir, char const *binname);
void parse_cmd(shell_t *shell);
void exec_cmd_heap(shell_t *shell);
int exec_cmd(shell_t *shell, int from_pipe);
void parse_arguments(char *lineptr, char ***argvptr, int *argcptr);
void parse_envvar(shell_t *shell, char *lineptr);
int parse_history(shell_t *shell, char *lineptr);
int exec_builtin(shell_t *shell, int from_pipe);
int exec_bin(shell_t *shell, int need_fork);
char *locate_bin(shell_t *shell, char const *name);
int builtin_cd(shell_t *shell);
int builtin_exit(shell_t *shell);
int builtin_env(shell_t *shell);
int builtin_setenv(shell_t *shell);
int builtin_unsetenv(shell_t *shell);
int builtin_which(shell_t *shell);
int builtin_where(shell_t *shell);
int builtin_repeat(shell_t *shell);
int builtin_echo(shell_t *shell);
int builtin_alias(shell_t *shell);
int builtin_export(shell_t *shell);
int builtin_unset(shell_t *shell);

/*
**  REDIRECTIONS / PIPES
*/
int exec_pipe(int *fds, int nmemb, int index, shell_t *shell);
int count_pipes(shell_t *shell);
int create_pipes(shell_t *shell);
void redirect_fds(shell_t *shell, int save[2]);
void update_instr_io(shell_t *shell, instr_t *instr);
void redirect_output(shell_t *shell, instr_t *instr, int is_double);
void redirect_input(shell_t *shell, instr_t *instr, int is_double);

/*
**  SEPARATORS
*/

void update_instr_separator(char **delims, instr_t *instr);
int check_separators(shell_t *shell);

/*
**  ALIAS
*/

data_node_t *source_shrc(void);
char *fetch_alias(shell_t *shell, char *name);
void replace_alias(shell_t *shell, char *line);

/*
**  JOBS
*/

struct jobs_s {
    jobs_t *next;
    jobs_t *prev;
    pid_t pid;
    int job_nb;
    char *name;
    char *status;
};

/* bg.c */
int exec_jobs_process(shell_t *shell, pid_t *pid);
int add_jobs_list(jobs_t *jobs, pid_t pid, char *name, char *status);
int builtin_process_bg(shell_t *shell);

/* fg.c */
int put_last_process_fg(shell_t *shell);
int choose_process_fg(shell_t *shell);
int builtin_fg(shell_t *shell);

/* jobs.c */
int print_job(int job_nb, char *status, char *name);
int builtin_jobs(shell_t *shell);

/* kill.c */
int kill_pid(shell_t *shell);
int kill_jobs(shell_t *shell);
int builtin_kill(shell_t *shell);

#endif /* !MYSH_H_ */
