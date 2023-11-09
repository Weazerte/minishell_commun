/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:25:22 by mderkaou          #+#    #+#             */
/*   Updated: 2023/11/09 13:39:24 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_free_child(t_cmds *data, t_env *lst_env)
{
	if (data->cmd)
		free(data->cmd);
	free_tab(data->env);
	if (data->infile != 0)
		close(data->infile);
	if (data->outfile != 1)
		close(data->outfile);
	free(data);
	ft_free_lst(lst_env);
}

void	exec_with_args(t_cmds *data_exec, int infile, int outfile, t_env *lst_env)
{
	char	**args;
	char	*path;
	int		status;

	status = 0;
	args = ft_split(data_exec->cmd, -7);
	path = ft_path_bin(args[0], lst_env);
	if (!path || !args)
	{
		if (args)
			free_tab(args);
		ft_putstr_fd("minishell: ", 2);
		change_fucked_char(data_exec->cmd);
		perror(data_exec->cmd);
		ft_free_child(data_exec, lst_env);
		exit(ERROR);
	}
	dup_and_close(infile, outfile);
	status = execve(path, args, data_exec->env);
	ft_memdel(path);
	free_tab(args);
	exit(status);
}


void	exec_without_args(t_cmds *data_exec, int infile, int outfile, t_env *lst_env)
{
	char	*path;
	char	*arr[2];
	int	status;

	path = ft_path_bin(data_exec->cmd, lst_env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		change_fucked_char(data_exec->cmd);
		perror(data_exec->cmd);
		ft_free_child(data_exec, lst_env);
		exit(EXIT_FAILURE);
	}
	arr[0] = path;
	arr[1] = NULL;
	dup_and_close(infile, outfile);		
	status = execve(path, arr, data_exec->env);
	ft_free_child(data_exec, lst_env);
	free(path);
	exit(status);
}
