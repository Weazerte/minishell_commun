/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:52:00 by weaz              #+#    #+#             */
/*   Updated: 2023/11/06 12:18:17 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>

#define MAGENTA "\033[95m"
#define RESET   "\033[0m"
#define DQM 1

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
    char    *env_line;
    struct s_env   *next;
} t_env;

typedef struct s_cmds
{
    char    *cmd; //le prompt du read line original avec si besoin le expend precise
    int infile; // 1 de base et autre si < ou <<
    int outfile; //0 de base et autre si > ou >>
    char **env;
    int exit;
    int ncmd;
    t_env *secret_lst_env; // lenvironement sous forme de liste chaine : je men occupe 
    t_env *lst_env;
} t_cmds;

char		*check_quotes(char *str);

int		syntax_parse(char *str);

int		syntax_error(char c);

int		is_digit(int c);

int		is_alpha(int c);

int		is_redirection(int c);

int		is_operator(char c);

int		is_space(char c);

int		operator_parse(char *str, char op);

size_t		ft_strlen(const char *s);

char 		*ft_strndup(const char *s, size_t n);

char 		*split_env(char *str);

char		*find_var_name(char *str, int i);

int		    find_pos_dollar(char *str);

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);

void	    ft_putinfd(char *content, int fd);

void	    ft_putinfd_n(char *content, int fd);

int		    exec(t_cmds **data_exec);

int			env_init(t_env **lst_env, char **env);

int	        ft_env_lstsize(t_env *lst);

int         env_builtin(t_env *lst_env, int fd);

char	    *ft_path_bin(char *cmd, t_env *lst_env);

void	    echo_builtin(int fd, char **args);

void		print_ordered_secret_env(t_env *env);

int			unset_builtin(char **a, t_env *lst_env);

int	        exit_builtin(t_cmds *data_exec, char **cmd);

int			cd_builtin(char **args, t_env *lst_env);

int			export_builtin(char **args, t_env *lst_env, t_env *lst_secret);

int		    pwd_builitn(int fd);

void	    multexec_with_builtin(t_cmds *data_exec, int i, int **pipe);

int	        exec_with_builtin(t_cmds *data_exec);

void	    ft_free_error(t_cmds *data, int **pipe);

void	    ft_free_one_ex(t_cmds *data);

int	        is_a_builtin(char *cmd);

void	    ft_free_mult_ex(t_cmds *data);

int	        init_pipe(t_cmds *data_exec, int ***pip);

void	    ft_pipe_action(t_cmds *data_exec, int **pipe, int i);

void	    ft_multexec_noargs(t_cmds *data_exec, int read_pipe, int write_pipe);

void	    ft_multexec_args(t_cmds *data_exec, int read_pipe, int write_pipe);

void	    ft_first_pipe(t_cmds *data_exec, int **pip);

void	    ft_inter_pipe(t_cmds *data_exec, int **pip, int i);

void	    ft_last_pipe(t_cmds *data_exec, int **pip, int i);

void	    exec_without_args(t_cmds *data_exec, int read_pipe, int write_pipe);

void	    exec_with_args(t_cmds *data_exec, int read_pipe, int write_pipe);

int	        make_all_exec(t_cmds *data_exec);

void	    ft_free_cmd(char *str, char **tab);

char	    *ft_find_bin(char **tab);

char	    *ft_cut_path(char *path);

char	    *ft_path(t_env *lst_env);

char	    *ft_path_bin(char *cmd, t_env *lst_env);

void	    ft_free_list(char **father);

void	    ft_close_pipes(t_cmds *data_exec, int **pipe);

void	    ft_free_error(t_cmds *data, int **pipe);

void	    ft_close_fd(int *fd);

int	        ft_verif_space(char *str);

void		increment_shell_level(t_env *lst_env);

char		*env_to_str(t_env *lst_env);

size_t		size_env(t_env *lst_env);

char	    *get_env_value(char *arg, t_env *lst_env);

char		*get_name_in_env(char *dest, const char *src);

void        free_tab(char **tab);

int			is_already_in_env(t_env *env, char *args);

int			env_add(char *line, t_env *lst_env);

int		    is_valid_env(const char *env);

void        ft_free_lst(t_env *lst);

int         find_next_pipe(char *str);

char        **line_to_tab(char *line);

t_cmds      *tab_to_struct(char **cmds);

char        *ft_positive(char *str);

char        *ft_parsing(char *start_line);

char		*dollar_qm(void);

char		*expand_all(char *str);

#endif
