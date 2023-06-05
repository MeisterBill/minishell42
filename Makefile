NAME		=	minishell

HEADER		=	./Includes/

LIBFT		=	libft/libft.a

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER)

SRCS		=	Sources/main.c \
					Sources/builtins.c \
					Sources/env.c \
					Sources/errors.c \
					Sources/exec_cmd.c \
					Sources/prompt.c \


OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all
