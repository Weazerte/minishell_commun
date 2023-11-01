NAME = minishell
SRCS = parse_main.c \
		parse_quotes.c \
		parse_syntax.c\
		parse_is_utils.c\
		parse_utils.c\
		parse_expand.c\
		
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
