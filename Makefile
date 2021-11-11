CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
LFLAGS		= -lreadline

INC_LINK	= -I./includes/

LIBFT_NAME      = libft.a
LIBFT_DIR       = ./libft/
LIBFT           = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

NAME		= minishell
SRC_DIR		= ./src/
C_FILES		= cd.c					\
			  echo.c				\
			  env.c					\
			  envp.c 				\
			  export.c 				\
			  get_next_line.c		\
			  get_next_line_utils.c	\
			  list_utils.c			\
			  main.c				\
			  parser.c				\
			  parser_utils.c		\
			  pwd.c 				\
			  str_split_recomb.c	\
			  unset.c 				\
			  utils.c				\
			  execute.c				\
			  test.c

SRCS		= $(addprefix $(SRC_DIR), $(C_FILES))
OBJS		= $(SRCS:.c=.o)

%.o			: %.c
	gcc -c $(CFLAGS) $(INC_LINK) $< -o $@

all			: $(LIBFT) $(NAME)

$(NAME)	: $(LIBFT) $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LFLAGS)

$(LIBFT)	:
	@make all -C $(LIBFT_DIR)

clean		:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean		:
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re			: fclean all

.PHONY		: all clean fclean re
