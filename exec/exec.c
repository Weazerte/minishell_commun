/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:03:20 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/09 16:23:20 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	is_exit(t_cmds *data)
{
	char **tab;

	tab = ft_split(data->cmd, -7);
	if (ft_strcmp(tab[0], "exit") == 0)
		    data->exit = 1;
	free_tab(tab);
}

int		one_exec(t_cmds *data_exec, t_env *lst_env)
{
	pid_t pid;
	int	status;

	status = 0;
	if (is_a_not_forked_builtin(data_exec->cmd) == 0)
		status = exec_with_not_forked_builtin(data_exec, lst_env);
	else 
	{
		pid = fork();
		if (pid == 0)
		{
			if (is_a_forked_builtin(data_exec->cmd) == 0)
				exec_with_forked_builtin(data_exec, lst_env);
			else if ((ft_verif_space(data_exec->cmd) == 1))
				exec_with_args(data_exec, data_exec->infile,
						data_exec->outfile, lst_env);
			else
				exec_without_args(data_exec, data_exec->infile,
						data_exec->outfile, lst_env);
		}
    	waitpid(pid, &status, 0);
	}
	is_exit(data_exec);
	g_exstatus = status;
	return (ft_free_one_ex(data_exec), 0);
}

void	exec(t_cmds *data_exec, t_env *lst_env)
{
	if (data_exec->ncmd == 1)
		one_exec(data_exec, lst_env);
    else
		make_multexec(data_exec, lst_env);
}
