/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:25:22 by mderkaou          #+#    #+#             */
/*   Updated: 2023/11/04 16:42:18 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_with_args(t_cmds *data_exec, int read_pipe, int write_pipe)
{
	char	**args;
	char	*path;

	args = ft_split(data_exec->cmd, ' ');
	path = ft_path_bin(args[0], data_exec->lst_env);
	if (!path || !args)
	{
		if (args)
			free_tab(args);
		ft_putstr_fd("minishell: ", 2);
		perror(data_exec->cmd);
		exit(ERROR);
	}
	if (write_pipe != 1)
	{
		dup2(write_pipe, STDOUT);
		close(write_pipe);
	}
	if (read_pipe != 0)
	{
		dup2(read_pipe, STDIN);
		close(read_pipe);
	}
	execve(path, args, data_exec->env);
	exit(-1);
}

void	exec_without_args(t_cmds *data_exec, int read_pipe, int write_pipe)
{
	char	*path;
	char	*arr[2];

	path = ft_path_bin(data_exec->cmd, data_exec->lst_env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(data_exec->cmd);
		exit(EXIT_FAILURE);
	}
	arr[0] = path;
	arr[1] = NULL;
	if (write_pipe != 1)
	{
		dup2(write_pipe, STDOUT);
		close(write_pipe);
	}
	if (read_pipe != 0)
	{
		dup2(read_pipe, STDIN);
		close(read_pipe);
	}
	execve(path, arr, data_exec->env);
	free(path);
	exit(-1);
}
