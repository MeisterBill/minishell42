NAME		=	libft.a

CFLAGS		=	-Wall -Wextra -Werror -g

HEADER		=	libft.h

SRCS		=	ft_atoi.c \
					ft_calloc.c \
					ft_is_x.c \
					ft_itoa.c \
					ft_matrix.c \
					ft_mem_x.c \
					ft_putx_fd.c \
					ft_split.c \
					ft_str_x.c \
					ft_str_x_2.c \
					get_next_line.c \


OBJ			=	${SRCS:.c=.o}

CC			= 	gcc

.c.o		:	${CC} ${CFLAGS} -c -I ${HEADER} $< -o ${<:.c=.o}

${NAME}		:	${OBJ} ${HEADER}
				ar rc ${NAME} ${OBJ}
				ranlib ${NAME}

all			:	${NAME}

clean:
				rm -f ${OBJ}

fclean		:	clean
				rm -f ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean
