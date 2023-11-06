#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAGENTA "\033[95m"
#define RESET "\033[0m"
#define DQM 1

typedef struct s_env
{
	char			*env_line;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	int				pipe;
	int				ncmd;
}					t_data;

typedef struct s_cmds
{
	char			*cmd;
	int				infile;
	int				outfile;
	t_env			env;
	t_data			data;
}t_cmds;

char				*check_quotes(char *str);
int					syntax_parse(char *str);
int					syntax_error(char c);
int					is_digit(int c);
int					is_alpha(int c);
int					is_redirection(int c);
int					is_operator(char c);
int					is_space(char c);
int					operator_parse(char *str, char op);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *s, size_t n);
char				*split_env(char *str, int dollar_pos);
char				*find_var_name(char *str, int i);
int					find_pos_dollar(char *str);
unsigned int		ft_strlcat(char *dest, char *src, unsigned int size);
int					find_nbcmd(char *str);
int					find_next_pipe(char *str);
char				*ft_positive(char *str);
int					free_struct(t_cmds *data_struct);
char				*dollar_qm(void);
char				*expand_all(char *str);
char	*build_expanded_line(char *before, char *value, char *after);
char	*rmv_spaces_quotes(char *line);
char	*negative_doublequotes(char *line);
void	here_sig(int sig);
void	is_inside_sig(int sig);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*delimit_to_path(char *line, char *limiter, char *filename);
char	*free_strs(char *str1, char *str2, char *str3);
char	*path_file(void);
char	*has_heredoc(char *line);
char	*find_multi_heredoc(char *line);
char	*find_heredoc(char *line);
char	*do_heredoc(char *line);
char	*find_delimit(char *line);
void	 ft_exec_heredoc(char *limiter, char *file);
void	inside_heredoc(char *limiter, char *file);
char	*ft_parsing(char *start_line);
unsigned int	count_malloc(int n);
char	*ft_itoa(int n);
int	ft_strcmp(char *s1, char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
t_cmds	*init_struct_cmds(int nbcmd);
char	*get_cleaned_split(char *line, int start, int end);
t_cmds	*fill_struct_cmd(t_cmds *struct_cmds, char *line, int *start, int *i);
t_cmds	*line_to_structs(char *line);
t_cmds	*free_struct_error(t_cmds *struct_cmds, int pos);
t_cmds	*init_struct_cmds(int nbcmd);
char	*create_and_clean_split(char *line, int start, int len);
t_cmds	*process_splits(char *line, t_cmds *struct_cmds, int *start, int *i);
void skip_spaces(const char **line);
char *clean_spaces_quotes(char *dest, const char *src, int *j, int i);
char	*ft_substr(char const *s, unsigned int start, size_t len);