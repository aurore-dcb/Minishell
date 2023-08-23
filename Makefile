# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 09:34:07 by aducobu           #+#    #+#              #
#    Updated: 2023/08/23 14:09:21 by aducobu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell

SRCS = 			${addprefix sources/, \
					${addprefix parsing/, parsing.c quotes.c split_meta.c list.c} \
					${addprefix exec/, main.c pwd.c env.c cd.c echo.c env_variables.c frees.c} \
				}

OBJS = 			${SRCS:sources/%.c=objects/%.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
EXECFLAGS = -lreadline
RM = rm -rf

LIBFT_DIR = libft
LIBFT_LIB = libft/libft.a

all: libft ${NAME}

libft/libft.a:
	make -C libft

${NAME}: ${OBJS} libft/libft.a Makefile
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT_LIB} ${EXECFLAGS}
	
objects/%.o: sources/%.c
	mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c -o $@ $^

clean:
	${RM} objects
	make -C libft clean

fclean: clean
	${RM} ${NAME}
	make -C libft fclean

re: fclean all