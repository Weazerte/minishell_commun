# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 15:11:22 by user              #+#    #+#              #
#    Updated: 2023/11/01 14:59:36 by user             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	parse/parse_main.c parse/parse_quotes.c parse/parse_syntax.c parse/parse_is_utils.c parse/parse_utils.c parse/parse_expand.c \
			exec/builtin.c exec/utils_exec.c exec/one_exec.c exec/mult_exec.c exec/main.c exec/ft_split_spec.c exec/exec_tools.c exec/clean_exec2.c exec/clean_exec.c \
			env/shellLVL.c env/ft_free.c env/get_env.c env/ft_putinfd.c env/env.c env/env_in_order.c \
			builtin/echo.c builtin/cd.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c builtin/unset.c


LIBS	=	-lreadline

NAME    =	minishell

OBJS    =	${SRCS:.c=.o}

CFLAGS	=	-Wall -Wextra -Werror -g

CC	=	cc

all:	${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	libft/libft.a ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBS} -Llibft -lft -o ${NAME} 

clean:
	rm -f ${OBJS}
	make -C libft clean

fclean:	clean
	rm -f ${NAME}
	make -C libft fclean

re:	fclean all

.PHONY:	all clean fclean re bonus

libft/libft.a:
	make -C libft
