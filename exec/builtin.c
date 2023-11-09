/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:47:24 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/09 13:26:17 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_with_not_forked_builtin(t_cmds *data_exec, t_env *lst_env)
{
	char **cmd_args;

	cmd_args = ft_split(data_exec->cmd, -7);
	if (ft_strncmp(data_exec->cmd, "cd", 2) == 0)
		cd_builtin(cmd_args, lst_env);
	else if (ft_strncmp(data_exec->cmd, "exit", 4) == 0)
		exit_builtin(cmd_args);
	else if (ft_strncmp(data_exec->cmd, "unset", 5) == 0)
		unset_builtin(cmd_args, lst_env);
	else if (ft_strncmp(data_exec->cmd, "export", 6) == 0)
		export_builtin(cmd_args, lst_env);
	if (cmd_args)
		free_tab(cmd_args);
	return (SUCCESS);
}

int	exec_with_forked_builtin(t_cmds *data_exec, t_env *lst_env)
{
	char **cmd_args;

	cmd_args = ft_split(data_exec->cmd, -7);
	if (ft_strncmp(data_exec->cmd, "echo", 4) == 0)
		echo_builtin(data_exec->outfile, cmd_args);
	else if (ft_strncmp(data_exec->cmd, "env", 3) == 0)
		env_builtin(lst_env, data_exec->outfile);
	else if (ft_strncmp(data_exec->cmd, "pwd", 3) == 0)
		pwd_builitn(/*data_exec->lst_env, */data_exec->outfile);
	ft_free_child(data_exec, lst_env);
	free_tab(cmd_args);
	exit(SUCCESS);
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

void	multexec_with_builtin(t_cmds *data_exec, int i, int **pipe, t_env *lst_env)
{
	char **cmd_args;

	cmd_args = ft_split(data_exec->cmd, -7);
	if (i < (data_exec->ncmd - 1))
	{
		ft_close_useless_pipe(data_exec, pipe, i);
		dup2(pipe[i][1], STDOUT);
		close(pipe[i][1]);
	}
	if (ft_strncmp(data_exec->cmd, "echo", 4) == 0)
		echo_builtin(data_exec->outfile, cmd_args);
	else if (ft_strncmp(data_exec->cmd, "env", 3) == 0)
		env_builtin(lst_env, data_exec->outfile);
	else if (ft_strncmp(data_exec->cmd, "pwd", 3) == 0)
		pwd_builitn(data_exec->outfile);
	if (cmd_args)
		free_tab(cmd_args);
	exit(1);
}
