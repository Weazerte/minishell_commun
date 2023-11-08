/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:05:08 by weaz              #+#    #+#             */
/*   Updated: 2023/11/08 22:04:54 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	dup_and_close(int infile, int outfile)
{
	if (outfile != 1)
	{
		dup2(outfile, STDOUT);
		close(outfile);
	}
	if (infile != 0)
	{
		dup2(infile, STDIN);
		close(infile);
	}
}

void	ft_multexec_args(t_cmds *data_exec, int infile, int outfile, t_env *lst_env)
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
		perror("error process");
		exit(ERROR);
	}
	dup_and_close(infile, outfile);
	status = execve(path, args, data_exec->env);
	ft_free_cmd(path, args);
	exit(status);
}

void	ft_multexec_noargs(t_cmds *data_exec, int infile, int outfile, t_env *lst_env)
{
	char	*path;
	char	*arr[2];
	int		status;

	status = 0;
	path = ft_path_bin(data_exec->cmd, lst_env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(data_exec->cmd);
		exit(EXIT_FAILURE);
	}
	arr[0] = path;
	arr[1] = NULL;
	dup_and_close(infile, outfile);
	status = execve(path, arr, data_exec->env);
	ft_memdel(path);
	exit(status);
}

int	make_multexec(t_cmds *data_exec, t_env *lst_env)
{
	int		i;
	pid_t		pid[1024];
	int	**pipe;
	int	status;

	if (init_pipe(data_exec, &pipe) == ERROR)
		return (perror("error process"), ft_free_error(data_exec, pipe), ERROR);
	i = 0;
	while (i < data_exec->ncmd)
	{
		// if ( multexec_fork(data_exec, pid, pipe, i) == 1)
		// 	return (ERROR);
		pid[i] = fork();
		if (pid[i] == -1)
		{
			return (perror("Error process"),
				ft_free_error(data_exec, pipe), exit(-1), ERROR);
		}
		if (pid[i] == 0)
		{
			if (is_a_forked_builtin(data_exec[i].cmd) == 0)
				multexec_with_builtin(&data_exec[i], i, pipe, lst_env);
			else
				pipe_redirect(&data_exec[i], pipe, i, lst_env);
		}
		i++;
	}
	ft_close_pipes(data_exec, pipe);
	i = -1;
	while (++i < data_exec->ncmd)
		waitpid(pid[i], &status, 0);
	ft_free_mult_ex(data_exec);
	return (status);
}
