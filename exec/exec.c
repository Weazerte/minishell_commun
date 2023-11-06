/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:03:20 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/06 22:04:00 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		one_pipe(t_cmds *data_exec)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		//si plusieur args
		if (is_a_builtin(data_exec->cmd) == 0)
			exec_with_builtin(data_exec);
		else if ((ft_verif_space(data_exec->cmd) == 1))
			exec_with_args(data_exec, data_exec->infile,
					data_exec->outfile);
		else
			exec_without_args(data_exec, data_exec->infile,
					data_exec->outfile);
	}
    waitpid(pid, NULL, 0);
	ft_free_one_ex(data_exec);
}

void		exec(t_cmds **data_exec)
{
    if ((*data_exec)->ncmd == 1)
    	one_pipe(*data_exec);
    else
    	make_all_exec(*data_exec);
}
