NAME	=	minishell

SRCS	=	main.c parsing/divide_prs.c  parsing/take_output.c parsing/struct_filling.c builtins/env.c \
			execute/execute.c execute/read_struct.c execute/child.c utils/execute_utils.c

OBJS = $(SRCS:.c=.o)


CC	=	gcc
RM	=	rm -rf
CFLAGS	= -Wall -Wextra -Werror
LIBFT = libft/libft.a
READLINE = readline

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(LIBFT) $(SRCS) -lreadline -o $(NAME)

clean:
		$(RM) $(OBJS) 

fclean: clean
		$(RM) $(NAME)

re: fclean all

run: re 
	./minishell

.PHONY: all clean fclean re