# Make variables
CFLAGS = -Wall -Wextra -Werror -MD -g3
CC = gcc
LIBFT = libft/libft.a
NAME = minishell

SRC = check_args.c builtins.c env.c errors.c			\
	  exec_cmd.c exec.c fill_list.c				\
	  get_cmd.c heredoc.c linked_list1.c main.c prompt.c		\
	  redir_pipe.c redirections.c signal.c	\
	  tokenize.c trim_quotes.c vars_path.c

OBJ = $(SRC:.c=.o)

# Cible par défaut
all: $(NAME)

# Création de l'exécutable
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@

# Compilation des fichiers sources en fichiers objets
%.o: src/%.c
	@$(CC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include $(CFLAGS) -c $< -o $@

# Création de l'archive statique libft.a
$(LIBFT):
	@make -C libft

clean:
	@make clean -C libft
	@$(RM) $(OBJ) $(OBJ:.o=.d)

fclean: clean
	@$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
