/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:52:00 by weaz              #+#    #+#             */
/*   Updated: 2023/11/09 16:59:13 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_exstatus;

# define MAGENTA "\033[95m"
# define RESET "\033[0m"
# define DQM 1

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define EXPANSION -36
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

typedef struct s_env
{
	char			*env_line;
	struct s_env	*next;
}					t_env;

typedef struct s_cmds
{
	char            *cmd;  
	int             infile;
	int             outfile;
	char			**env;
	int				exit;
	int				ncmd;
	// t_env			*lst_env;
}					t_cmds;

int					ft_tab_len(char **env);

int					exec_with_not_forked_builtin(t_cmds *data_exec, t_env *lst_env);

void				ft_put_unknow_cmd(char *cmd);

void				exec(t_cmds *data_exec, t_env *lst_env);

int					ft_env_lstsize(t_env *lst);

void				ft_free_one_ex(t_cmds *data);

char				**env_to_tab(t_env *lst_env);

void				ft_putinfd(char *content, int fd);

void				ft_putinfd_n(char *content, int fd);

int					env_init(t_env **lst_env, char **env);

int					env_builtin(t_env *lst_env, int fd);

char				*ft_path_bin(char *cmd, t_env *lst_env);

void				echo_builtin(int fd, char **args);

void				print_ordered_secret_env(t_env *env);

int					unset_builtin(char **a, t_env *lst_env);

int					is_a_not_forked_builtin(char *cmd);

int					is_a_forked_builtin(char *cmd);

int					cd_builtin(char **args, t_env *lst_env);

int					export_builtin(char **args, t_env *lst_env);

void				dup_and_close(int infile, int outfile);

int					pwd_builitn(int fd);

int					exec_with_forked_builtin(t_cmds *data_exec, t_env *lst_env);

void				multexec_with_builtin(t_cmds *data_exec, int i, int **pipe, t_env *lst_env);

void				ft_multexec_args(t_cmds *data_exec, int infile,
						int outfile, t_env *lst_env);

void				ft_multexec_noargs(t_cmds *data_exec, int infile,
						int outile, t_env *lst_env);

void				ft_first_pipe(t_cmds *data_exec, int **pipe, t_env *lst_env);

void				ft_inter_pipe(t_cmds *data_exec, int **pipe, int i, t_env *lst_env);

void				ft_last_pipe(t_cmds *data_exec, int **pipe, int i, t_env *lst_env);

void				exec_without_args(t_cmds *data_exec, int infile,
						int outfile, t_env *lst_env);

void				exec_with_args(t_cmds *data_exec, int infile,
						int outfile, t_env *lst_env);

void				make_multexec(t_cmds *data_exec, t_env *lst_env);

char				**ft_split_dos(char *s, char c, char *exe);

char				*ft_find_bin(char **tab);

char				*ft_cut_path(char *path);

char				*ft_path(t_env *lst_env);

void				ft_close_pipes(t_cmds *data_exec, int **pipe);

void				ft_free_error(t_cmds *data, int **pipe);

void				ft_free_cmd(char *str, char **tab);

void				ft_free_mult_ex(t_cmds *data);

void				ft_close_fd(int *fd);

int					exit_builtin(char **cmd);

int					ft_verif_space(char *str);

void				increment_shell_level(t_env *lst_env);

char				*env_to_str(t_env *lst_env);

size_t				size_env(t_env *lst_env);

char				*get_env_value(char *arg, t_env *lst_env);

char				*get_name_in_env(char *dest, const char *src);

void				free_tab(char **tab);

int					is_already_in_env(t_env *env, char *args);

int					env_add(char *line, t_env *lst_env);

int					is_valid_env(const char *env);

void				ft_free_lst(t_env *lst);

void				pipe_redirect(t_cmds *data_exec, int **pipe, int i, t_env *lst_env);

int					init_pipe(t_cmds *data_exec, int ***pipe);

void				change_fucked_char(char *s);

char				*ft_join_path(char *src, char *cmd);

void				ft_free_child(t_cmds *data, t_env *lst_env);

void				ft_open_outfile(t_cmds *data);

void				ft_open_infile(t_cmds *data);

char				*check_quotes(char *str);
int					syntax_parse(char *str);
int					syntax_error(char c);
int					is_digit(int c);
int					is_alpha(int c);
int					is_redirection(int c);
int					is_operator(char c);
int					is_space(char c);
int					operator_parse(char *str, char op);
char				*split_env(char *str, int dollar_pos, t_env *backup_env);
char				*find_var_name(char *str, int i);
int					find_pos_dollar(char *str);
int					find_nbcmd(char *str);
int					find_next_pipe(char *str);
char				*ft_positive(char *str);
int					free_struct(t_cmds *data_struct);
char				*dollar_qm(void);
char				*expand_all(char *str, t_env *backup_env);
char				*build_expanded_line(char *before, char *value,
						char *after);
char				*rmv_spaces_quotes(char *line);
char				*negative_doublequotes(char *line);
void				here_sig(int sig);
void				is_inside_sig(int sig);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*delimit_to_path(char *line, char *limiter, char *filename);
char				*free_strs(char *str1, char *str2, char *str3);
char				*path_file(void);
char				*has_heredoc(char *line);
char				*find_multi_heredoc(char *line);
char				*find_heredoc(char *line);
char				*do_heredoc(char *line, int i);
char				*find_delimit(char *line);
void				ft_exec_heredoc(char *limiter, char *file);
void				inside_heredoc(char *limiter, char *file);
char				*ft_parsing(char *start_line, t_env *backup_env);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_cmds				*init_struct_cmds(int nbcmd);
t_cmds				*line_to_structs(char *line);
t_cmds				*free_struct_error(t_cmds *struct_cmds, int pos);
char				*create_and_clean_split(char *line, int start, int len);
t_cmds				*process_splits(char *line, t_cmds *struct_cmds, int *start,
						int *i);
void				skip_spaces(const char **line);
char				*clean_spaces_quotes(char *dest, const char *src, int *j,
						int i);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char                *ft_strndup(const char *s, size_t n);
unsigned int	     ft_strlcat(char *dest, char *src, unsigned int size);
void	ft_exit(void);
void	handle_sigint(int sig);
void init_signal(void);
t_cmds *do_parsing(char *start_line, t_env *backup_env);
char *ft_get_env(t_env *env_list, const char *name);
void csq(char *dest, const char *src, int *j, int *i);

#endif
