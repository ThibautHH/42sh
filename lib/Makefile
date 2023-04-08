##
## EPITECH PROJECT, 2023
## libice
## File description:
## Makefile
##

NAME		:=	libice.a

DIR			:=	./
SRC			:=

DIR_ICE		:=	./ice/

DIR			+=	$(addprefix $(DIR_ICE), ./array/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_array_len.c	\
				ice_free_array.c\
				)

DIR			+=	$(addprefix $(DIR_ICE), ./int/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_atoi.c		\
				ice_itoa.c		\
				ice_utoa.c		\
				ice_btoa.c		\
				ice_ftoa.c		\
				ice_strtol.c	\
				ice_intlen.c	\
				)

DIR			+=	$(addprefix $(DIR_ICE), ./memory/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_realloc.c	\
				ice_calloc.c	\
				ice_memchr.c	\
				ice_memcmp.c	\
				ice_memcpy.c	\
				ice_memset.c	\
				)

DIR			+=	$(addprefix $(DIR_ICE), ./output/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_puts.c		\
				ice_dputs.c		\
				)

DIR			+=	$(addprefix $(DIR_ICE), ./printf/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_printf.c	\
				ice_dprintf.c	\
				ice_sprintf.c	\
				ice_snprintf.c	\
				ice_asprintf.c	\
				)

DIR			+=	$(addprefix $(lastword $(DIR)), ./private/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				handle_format.c			\
				get_argument.c			\
				add_buffer.c			\
                add_width.c				\
				ice_printf_char.c		\
				ice_printf_str.c		\
				ice_printf_percent.c	\
				ice_printf_int.c		\
				ice_printf_uint.c		\
				ice_printf_binary.c		\
				ice_printf_octal.c		\
				ice_printf_hexa.c		\
				ice_printf_hexa_upper.c	\
				ice_printf_ptr.c		\
				ice_printf_len.c		\
				ice_printf_float.c		\
				)

DIR			+=	$(addprefix $(DIR_ICE), ./string/)
SRC			+=	$(addprefix $(lastword $(DIR)),\
				ice_strcat.c	\
				ice_strcmp.c	\
				ice_strcpy.c	\
				ice_strdup.c	\
				ice_strlen.c	\
				ice_strncat.c	\
				ice_strncmp.c	\
				ice_strncpy.c	\
				ice_strndup.c	\
				ice_strnrev.c	\
				ice_strrev.c	\
				ice_strswap.c	\
				ice_strsplit.c	\
				ice_strstr.c	\
				ice_strchr.c	\
				ice_strtrim.c	\
				)

DIR			+=	./list/
SRC			+=	$(addprefix $(lastword $(DIR)),\
				list_add_node.c		\
				list_add.c			\
				list_create.c		\
				list_destroy.c		\
				list_destroy_node.c	\
				list_get.c			\
				list_pop.c			\
				list_pop_node.c		\
				list_remove.c		\
				list_remove_node.c	\
				list_sort.c			\
				)

DIR_TEST	:=	../tests/
SRC_TEST	:=	$(addprefix $(DIR_TEST),\
				test_array.c		\
				test_int.c			\
				test_output.c		\
				test_printf.c		\
				test_string.c		\
				test_memory.c		\
				test_list.c			\
				)

DIR_BUILD	:=	../build/

ROOT_OBJ	:=	$(addprefix $(DIR_BUILD), ./obj/)
DIR_OBJ		:=	$(addprefix $(ROOT_OBJ), $(DIR))
OBJ			:=	$(patsubst %.c, $(ROOT_OBJ)%.o, $(SRC))

TEST_DIR	:=	$(addprefix $(DIR_BUILD), ./tests/)
UNIT_TEST	:=	./unit_test

RM			:=	rm -rf

CC			:=	gcc
CLINKER		:=	ar rc
CFLAGS		:=	-I./../include/ -Wall -Wextra

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
	@$(CLINKER) $@ $(OBJ)\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@\
	|| printf "\033[31m[ERROR]\033[0m %s\n" $@

$(UNIT_TEST):		CFLAGS += -lcriterion --coverage
$(UNIT_TEST):		fclean
	mkdir -p $(TEST_DIR)
	@$(CC) $(CFLAGS) $(SRC) $(SRC_TEST) -o $(TEST_DIR)$@\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@\
	|| printf "\033[31m[ERROR]\033[0m %s\n" $@

tests_run:			$(UNIT_TEST)
	@./$(TEST_DIR)$(UNIT_TEST)
	gcovr $(TEST_DIR) --exclude tests/

debug:				CFLAGS += -g
debug:				re

clean:
	@[ -d $(DIR_BUILD) ]\
	&& $(RM) $(DIR_BUILD)\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(DIR_BUILD) || true

fclean:				clean
	@[ -f $(NAME) ]\
 	&& $(RM) $(NAME)\
 	&& printf "\033[31m[DELETED]\033[0m %s\n" $(NAME) || true

re:					fclean all

.PHONY:				all clean fclean re
