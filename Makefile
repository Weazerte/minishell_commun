# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 15:11:22 by user              #+#    #+#              #
#    Updated: 2023/11/15 20:40:57 by eaubry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main/main.c \
			exec/builtin.c exec/builtin_tools.c exec/ft_free.c exec/pipe_exec.c exec/one_exec.c exec/mult_exec.c exec/exec.c exec/ft_split_spec.c exec/exec_tools.c exec/clean_exec.c \
			env/shellLVL.c env/get_env.c env/ft_putinfd.c env/env.c env/env_in_order.c \
			builtin/echo.c builtin/cd.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c builtin/unset.c \
			parse/ft_open_infile.c parse/ft_open_outfile.c parse/parse_main.c parse/parse_utils2.c parse/parse_syntax_quotes.c parse/parse_is_utils.c parse/parse_utils.c parse/parse_expand.c parse/parse_signal.c parse/parse_heredoc.c parse/parse_heredoc_utils.c parse/parse_cmd.c\

LIBS	=	-lreadline

NAME    =	minishell

OBJS    =	${SRCS:.c=.o}

CFLAGS	=	-Wall -Wextra -Werror -ggdb

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
	
#val:		$(NAME)
#		valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=rl_ignore --track-origins=yes ./${NAME}

re:	fclean all

.PHONY:	all clean fclean re bonus

libft/libft.a:
	make -C libft
