##
## EPITECH PROJECT, 2023
## minishell2
## File description:
## Makefile
##

NAME		:=	42sh

DIR			:=	./
SRC			:=
LIB			:=	./lib/

DIR_SRC		+=	./src/

SRC			+=	$(addprefix $(DIR_SRC),\
				main.c				\
				)

DIR			+=	$(addprefix $(DIR_SRC), ./miscellaneous/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				get_argument.c		\
				display_error.c		\
				execute_binary.c	\
				)

DIR			+=	$(addprefix $(DIR_SRC), ./builtin/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				builtin_cd.c					\
				builtin_exit.c					\
				builtin_env.c					\
				builtin_setenv.c				\
				builtin_unsetenv.c				\
				)

DIR			+=	$(addprefix $(DIR_SRC), ./env/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				get_env.c						\
				set_env.c						\
				unset_env.c						\
				display_env.c					\
				exit_env.c						\
				)

DIR			+= 	$(addprefix $(DIR_SRC), ./env/initialisation/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				load_env.c		\
				dup_env.c		\
				fix_env.c		\
				destroy_env.c	\
				)

DIR			+=	$(addprefix $(DIR_SRC), ./search/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				search_function.c				\
				)

DIR			+=	$(addprefix $(DIR_SRC), ./parser/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				handle_input.c		\
				handle_sequence.c	\
				handle_pipe.c		\
				redirection.c		\
				output.c			\
				input.c				\
				get_input.c			\
				extract.c			\
				)

DIR_TEST	:=	./tests/
SRC_TEST	:=	$(addprefix $(DIR_TEST),\
				)

DIR_BUILD	:=	./build/

ROOT_OBJ	:=	$(addprefix $(DIR_BUILD), ./obj/)
DIR_OBJ		:=	$(addprefix $(ROOT_OBJ), $(DIR))
OBJ			:=	$(patsubst %.c, $(ROOT_OBJ)%.o, $(SRC))

UNIT_TEST	:=	./unit_test


RM			:=	rm -rf
MAKE		:=	make -sC$(LIB) -j

CC			:=	gcc
CFLAGS		:=	-I./include/ -Wall -Wextra
LDFLAGS		:=	-L$(LIB)
LDLIBS		:=	-lice

all:				$(DIR_OBJ) $(NAME)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)\
	&& printf "\033[93m[CREATED]\033[0m %s\n" $(DIR_OBJ)\
	|| printf "\033[31m[ERROR]\033[0m %s\n" $(DIR_OBJ)

$(ROOT_OBJ)%.o:		%.c
	@$(CC) $(CFLAGS) -c $< -o $@\
	&& printf "\033[32m[OK]\033[0m %s\n" $<\
	|| printf "\033[31m[KO]\033[0m %s\n" $<

$(NAME):			$(OBJ)
	@$(MAKE)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)\
	&& printf "\033[32m[SUCCESS]\033[0m %s\n" $@\
	|| printf "\033[31m[ERROR]\033[0m %s\n" $@

$(UNIT_TEST):
	@$(MAKE) $(UNIT_TEST)

tester:				all
	@./tests/$@/tester.sh

tests_run:			tester
	@$(MAKE) $@

lib_all:
	@$(MAKE) all

lib_re:
	@$(MAKE) re

lib_debug:
	@$(MAKE) debug

debug:				CFLAGS += -g
debug:				lib_debug re

clean:
	@$(MAKE) $@
	@[ -d $(ROOT_OBJ) ]\
	&& $(RM) $(ROOT_OBJ)\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(ROOT_OBJ) || true

fclean:				clean
	@$(MAKE) $@
	@[ -f $(NAME) ]\
	&& $(RM) $(NAME)\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(NAME) || true

re:					fclean all

.PHONY:				all clean fclean re $(NAME)

.SILENT:			all test_run test_coverage debug clean fclean re
