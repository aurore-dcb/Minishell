# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aducobu <aducobu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 09:34:07 by aducobu           #+#    #+#              #
#    Updated: 2023/09/22 10:10:20 by aducobu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell

SRCS = 			${addprefix sources/, \
					${addprefix parsing/, parsing.c quotes.c \
					 	list.c split_pipe.c error_handling.c expand.c \
					 	expand_count.c expand_apply.c expand_special.c split_word.c \
						list_env.c parse_env.c get_end_word.c} \
					${addprefix exec/, main.c frees.c frees2.c exec_utils.c \
						pipex.c get_paths.c files.c process.c find_path.c pids.c \
						here_doc.c error.c shlvl.c} \
					${addprefix builtins/, pwd.c env.c cd.c echo.c export.c \
						export_utils.c export_utils2.c unset.c builtins.c \
						exit.c cd_utils.c } \
					${addprefix signal/, init_sig.c } \
				}

OBJS = 			${SRCS:sources/%.c=objects/%.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
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