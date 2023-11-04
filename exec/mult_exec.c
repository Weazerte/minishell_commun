/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:05:08 by weaz              #+#    #+#             */
/*   Updated: 2023/11/04 20:04:50 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_multexec_args(t_cmds *data_exec, int read_pipe, int write_pipe)
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
		perror("error process");
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
	ft_free_cmd(path, args);
	exit(-1);
}

void	ft_multexec_noargs(t_cmds *data_exec, int read_pipe, int write_pipe)
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
		if (write_pipe != 0 && write_pipe != -1)
	{
		dup2(write_pipe, STDOUT);
		close(write_pipe);
	}
	if (read_pipe != 1 && read_pipe != -1)
	{
		dup2(read_pipe, STDIN);
		close(read_pipe);
	}
	execve(path, arr, data_exec->env);
	ft_memdel(path);
}


int	make_all_exec(t_cmds *data_exec)
{
	
	int		i;
	pid_t		pid[1024];
	int	**pipe;

	//verifier error
	if (init_pipe(data_exec, &pipe) == ERROR)
		return (perror("error process"), ft_free_error(data_exec, pipe), ERROR);
	i = 0;
	while (i < data_exec->ncmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			return (perror("Error process"),
				ft_free_error(data_exec, pipe), exit(-1), ERROR);
		}
		if (pid[i] == 0)
		{
			if (is_a_builtin(data_exec[i].cmd) == 0)
				multexec_with_builtin(&data_exec[i], i, pipe);
			else
				ft_pipe_action(&data_exec[i], pipe, i);
		}
		i++;
	}
	ft_close_pipes(data_exec, pipe);
	i = -1;
	while (++i < data_exec->ncmd)
		waitpid(pid[i], NULL, 0);
		// if (data_exec[i].need2wait == 1)
	ft_free_mult_ex(data_exec);
	return (0);
}
