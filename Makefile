# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 09:34:07 by aducobu           #+#    #+#              #
#    Updated: 2023/08/22 14:12:26 by aducobu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell

SRCS = 			exec/main_exec.c \
				exec/pwd.c \
				exec/env.c \
				exec/cd.c \
				exec/echo.c \
				exec/env_variables.c \
				parsing/quotes.c

OBJS = 			${SRCS:exec/%.c=objects/%.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
EXECFLAGS = -lreadline
RM = rm -rf

LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a

all: libft ${NAME}

libft/libft.a:
	make -C libft

${NAME}: objects ${OBJS} libft/libft.a Makefile
	${CC} ${CFLAGS} ${EXECFLAGS} -o ${NAME} ${OBJS} ${LIBFT_LIB}

objects:
	mkdir -p objects

objects/%.o: exec/%.c | objects
	${CC} ${CFLAGS} -o $@ -c $<

clean:
	${RM} objects
	make -C libft clean

fclean: clean
	${RM} ${NAME}
	make -C libft fclean

re: fclean all