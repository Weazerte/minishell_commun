/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:25:22 by mderkaou          #+#    #+#             */
/*   Updated: 2023/11/01 12:36:36 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_with_args(t_cmds *data_exec, int read_pipe, int write_pipe)
{
	char	**str;
	char	*path;

	str = ft_split(data_exec->cmd, ' ');
	path = ft_path_bin(str[0], data_exec->lst_env);
	if (!path || !str)
	{
		if (str)
			ft_free_tabx2(str);
		ft_putstr_fd("minishell: ", 2);
		perror(data_exec->cmd);
		ft_free_int(data_exec, -1);
		exit(EXIT_FAILURE);
	}
	//si pas stdin ou pas stdout close it
	if (write_pipe != 0 && write_pipe != -1)
	{
		dup2(write_pipe, STDOUT_FILENO);
		close(write_pipe);
	}
	if (read_pipe != 1 && read_pipe != -1)
	{
		dup2(read_pipe, STDIN_FILENO);
		close(read_pipe);
	}
	execve(path, str, data_exec->env);
	ft_free_int(data_exec, -1);
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
		ft_free_int(data_exec, -1);
		exit(EXIT_FAILURE);
	}
	arr[0] = path;
	arr[1] = NULL;
	//si pas stdin ou pas stdout close it
	if (write_pipe != 0 && write_pipe != -1)
	{
		dup2(write_pipe, STDOUT_FILENO);
		close(write_pipe);
	}
	if (read_pipe != 1 && read_pipe != -1)
	{
		dup2(read_pipe, STDIN_FILENO);
		close(read_pipe);
	}
	execve(path, arr, data_exec->env);
	free(path);
	ft_free_int(data_exec, -1);
	exit(-1);
}
