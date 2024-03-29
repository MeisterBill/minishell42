# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 18:28:24 by artvan-d          #+#    #+#              #
#    Updated: 2023/07/22 18:30:18 by artvan-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -MD -g3
CC = gcc
LIBFT = libft/libft.a
NAME = minishell

SRC_DIR = src
OBJ_DIR = obj

SRC = check_args.c builtins.c env.c \
	errors.c exec.c fill_list.c \
	get_cmd.c heredoc.c linked_list1.c main.c prompt.c		\
	redir_pipe.c redirections.c signal.c	\
	tokenize.c trim_quotes.c vars_path.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make clean -C libft
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME) $(LIBFT)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
