# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artvan-d <artvan-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 18:28:20 by artvan-d          #+#    #+#              #
#    Updated: 2023/07/22 18:42:00 by artvan-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CFLAGS		=	-Wall -Wextra -Werror -g

HEADER		=	libft.h

SRCS		=	ft_atoi.c \
					ft_calloc.c \
					ft_is_x.c \
					ft_itoa.c \
					ft_matrix.c \
					ft_putx_fd.c \
					ft_mem_x.c \
					ft_split.c \
					ft_str_x.c \
					ft_str_x_2.c \
					ft_str_x_3.c \
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
