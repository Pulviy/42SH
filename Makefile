##
## EPITECH PROJECT, 2019
## PSU_minishell1_2018
## File description:
## Makefile
##

SRC		=	src/main.c							\
			src/ll/data_node.c					\
			src/ll/list.c						\
			src/ll/utils.c						\
			src/ll/instr.c						\
			src/sh/shell.c						\
			src/sh/env.c						\
			src/sh/alias.c						\
			src/editor/editor.c					\
			src/editor/cursor.c					\
			src/editor/prompt.c					\
			src/editor/termios.c				\
			src/editor/bind/keybind.c			\
			src/editor/bind/arrows.c			\
			src/editor/bind/ctrl.c				\
			src/builtin/init_builtins_list.c	\
			src/builtin/cd.c					\
			src/builtin/exit.c					\
			src/builtin/env.c					\
			src/builtin/which.c					\
			src/builtin/where.c					\
			src/builtin/echo.c					\
			src/builtin/repeat.c				\
			src/builtin/alias.c					\
			src/builtin/locals.c				\
			src/builtin/kill.c					\
			src/builtin/jobs.c					\
			src/builtin/bg.c					\
			src/builtin/fg.c					\
			src/cmd/exec_builtins.c				\
			src/cmd/exec.c						\
			src/cmd/redir.c						\
			src/cmd/pipe.c						\
			src/cmd/args.c						\
			src/cmd/bin.c						\
			src/cmd/parse.c						\
			src/cmd/parse_history.c				\
			src/cmd/parse_var.c					\
			src/cmd/separators.c				\
			src/history/history.c				\
			src/history/interface.c				\
			src/completion/get_completion.c		\
			src/completion/show_completion.c	\
			src/completion/cmdline_split.c		\
			src/utils/readline.c				\
			src/utils/is_file.c					\
			src/utils/is_file_elf.c				\
			src/utils/put_usage.c				\
			src/utils/siginit.c					\
			src/utils/getcpos.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Iinclude -Wall -Wextra

CLIBS	=

NAME	=	42sh

DEBUG ?= 0

ifneq ($(DEBUG), 0)
	CFLAGS += -g
endif

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc $(OBJ) -o $(NAME) $(CFLAGS) $(CLIBS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

debug:
	make DEBUG=1

history_clear:
	@printf "" > conf/.42sh_history

rc_clear:
	@printf "" > conf/.42shrc

run: all
	./$(NAME)

.PHONY: all clean fclean re debug history_clear rc_clear run
