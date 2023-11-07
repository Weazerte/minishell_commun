/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:03:20 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/07 15:42:39 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	is_exit(t_cmds *data)
{
	char **tab;

	tab = ft_split(data->cmd, -7);
	if (ft_strcmp(tab[0], "exit") == 0)
		    data->exit = 1;
	if (tab)
		free_tab(tab);
}

int		one_exec(t_cmds *data_exec)
{
	pid_t pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (is_a_builtin(data_exec->cmd) == 0)
			exec_with_builtin(data_exec);
		else if ((ft_verif_space(data_exec->cmd) == 1))
			exec_with_args(data_exec, data_exec->infile,
					data_exec->outfile);
		else
			exec_without_args(data_exec, data_exec->infile,
					data_exec->outfile);
	}
    waitpid(pid, &status, 0);
	is_exit(data_exec);
	ft_free_one_ex(data_exec);
	return (status);
}

void	exec(t_cmds **data_exec)
{
	if ((*data_exec)->ncmd == 1)
		exit_status = one_exec(*data_exec);
    else
	{
		exit_status = make_multexec(*data_exec);
	}
}
