# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 19:26:20 by eaubry            #+#    #+#              #
#    Updated: 2023/11/04 20:18:32 by eaubry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    =	ft_bzero.c ft_calloc.c ft_strcmp.c ft_isalnum.c ft_strisnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memdel.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_atoi.c

INC    =	libft.h

BONUS	=	ft_lstclear.c ft_lstadd_back.c ft_lstadd_front.c ft_lstmap.c ft_lstnew.c ft_lstdelone.c ft_lstlast.c ft_lstsize.c ft_lstiter.c 

NAME    =	libft.a

OBJS    =	${SRCS:.c=.o}

OBJSB	= ${BONUS:.c=.o}

CFLAGS    =    -Wall -Wextra -Werror

all:	${NAME}

.c.o:
	cc ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} 
	ar rcs ${NAME} ${OBJS} ${INC}

clean:
	rm -f ${OBJS} ${OBJSB}

fclean:	clean
	rm -f ${NAME}

bonus:	${OBJS} ${OBJSB}
	ar rcs ${NAME} ${OBJS} ${OBJSB} ${INC}

re:	fclean all

so:
	$(CC) -fPIC $(CFLAGS) $(SRC)
	gcc -shared -o libft.so $(OBJ)

.PHONY:	all clean fclean re bonus
