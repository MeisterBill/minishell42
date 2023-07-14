NAME		=	minishell

HEADER		=	./Includes/

LIBFT		=	libft/libft.a

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER)

LDLIBS   = -L/Users/Arthur/.brew/Cellar/readline/8.2.1 -lreadline

LDFLAGS = -L/Users/Arthur/.brew/Cellar/readline/8.2.1

CPPFLAGS = -I/Users/Arthur/.brew/Cellar/readline/8.2.1/include


SRCS		=	Sources/main.c \
					Sources/builtins.c \
					Sources/env.c \
					Sources/errors.c \
					Sources/exec_cmd.c \
					Sources/prompt.c \
					Sources/check_args.c \
					Sources/tokenize.c \
					Sources/vars_path.c \
					Sources/redir_pipe.c \
					Sources/fill_list.c \
					Sources/trim_quotes.c \
					Sources/linked_list1.c \
					Sources/redirections.c \
					Sources/signal.c \
					Sources/heredoc.c \


OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
				$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LDLIBS)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all
