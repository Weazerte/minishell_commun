/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:47:24 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/06 21:58:00 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_a_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (0);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (0);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (0);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (0);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (0);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (0);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (0);
	return (1);
}

void	exec_with_builtin(t_cmds *data_exec)
{
	char **cmd_args;

	cmd_args = ft_split(data_exec->cmd, ' ');
	if (ft_strncmp(data_exec->cmd, "echo", 4) == 0)
		echo_builtin(data_exec->outfile, cmd_args);
	else if (ft_strncmp(data_exec->cmd, "cd", 2) == 0)
		cd_builtin(cmd_args, data_exec->lst_env);
	else if (ft_strncmp(data_exec->cmd, "env", 3) == 0)
		env_builtin(data_exec->lst_env, data_exec->outfile);
	else if (ft_strncmp(data_exec->cmd, "exit", 4) == 0)
		exit_builtin(data_exec, cmd_args);
	else if (ft_strncmp(data_exec->cmd, "unset", 5) == 0)
		unset_builtin(cmd_args, data_exec->lst_env);
	else if (ft_strncmp(data_exec->cmd, "export", 6) == 0)
		export_builtin(cmd_args, data_exec->lst_env, data_exec->secret_lst_env);
	else if (ft_strncmp(data_exec->cmd, "pwd", 3) == 0)
		pwd_builitn(data_exec->outfile);
	if (cmd_args)
		free_tab(cmd_args);
}

void	ft_close_useless_pipe(t_cmds *data, int **pipe, int  i)
{
	int	j;


	j = 0;
	close(pipe[i][0]);
	while (j < (data->ncmd - 1))
	{
		if (j != i)
		{
			close (pipe[j][0]);
			close (pipe[j][1]);
		}
		j++;
		}
}

void	multexec_with_builtin(t_cmds *data_exec, int i, int **pipe)
{
	char **cmd_args;

	cmd_args = ft_split(data_exec->cmd, -7);
	if (i < (data_exec->ncmd - 1))
	{
		ft_close_useless_pipe(data_exec, pipe, i);
		dup2(pipe[i][1], STDOUT);
		close(STDOUT);
	}
	if (ft_strncmp(data_exec->cmd, "echo", 4) == 0)
		echo_builtin(data_exec->outfile, cmd_args);
	else if (ft_strncmp(data_exec->cmd, "env", 3) == 0)
		env_builtin(data_exec->lst_env, data_exec->outfile);
	else if (ft_strncmp(data_exec->cmd, "pwd", 3) == 0)
		pwd_builitn(data_exec->outfile);
	if (cmd_args)
		free_tab(cmd_args);
	exit(1);
}
