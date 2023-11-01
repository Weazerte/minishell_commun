/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:47:24 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/01 13:14:05 by eaubry           ###   ########.fr       */
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

int	exec_with_builtin(t_cmds *data_exec)
{
	int	ret;
	char **cmd_args;

	ret = 0;
	cmd_args = ft_split(data_exec->cmd, ' ');
	if (ft_strncmp(data_exec->cmd, "echo", 4) == 0)
		echo_builtin(data_exec->outfile, data_exec->cmd);
	else if (ft_strncmp(data_exec->cmd, "cd", 2) == 0)
		ret = cd_builtin(cmd_args, data_exec->lst_env);
	else if (ft_strncmp(data_exec->cmd, "env", 3) == 0)
	{
		printf("jsuisla\n");
		ret = env_builtin(data_exec->lst_env);
	}
	else if (ft_strncmp(data_exec->cmd, "exit", 4) == 0)
		ret = exit_builtin(cmd_args);
	else if (ft_strncmp(data_exec->cmd, "unset", 5) == 0)
		ret = unset_builtin(cmd_args, data_exec->lst_env);
	else if (ft_strncmp(data_exec->cmd, "export", 6) == 0)
		ret = export_builtin(cmd_args, data_exec->lst_env, data_exec->secret_lst_env);
	else if (ft_strncmp(data_exec->cmd, "pwd", 3) == 0)
		ret = pwd_builitn();
	if (cmd_args)
		free(cmd_args);
	return (ret);
}

