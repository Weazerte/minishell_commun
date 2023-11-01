#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define MAGENTA "\033[95m"
#define RESET   "\033[0m"
#define DQM 1

typedef struct s_env
{
    char    *env_line;
    struct s_env   *next;
} t_env;

typedef struct s_data
{
	int pipe;
	int ncmd;
}t_data;

typedef struct s_cmds
{
	char 	*cmd;
	int		infile;
	int		outfile;
	t_env	env;
	t_data	data;
}t_cmds;

char	*check_quotes(char *str);
int		syntax_parse(char *str);
int		syntax_error(char c);
int		is_digit(int c);
int		is_alpha(int c);
int		is_redirection(int c);
int		is_operator(char c);
int		is_space(char c);
int		operator_parse(char *str, char op);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char *ft_strndup(const char *s, size_t n);
char *split_env(char *str);
char	*find_var_name(char *str, int i);
size_t	find_pos_dollar(char *str);
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);