/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:05:08 by weaz              #+#    #+#             */
/*   Updated: 2023/11/01 14:08:37 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pipe_action(t_cmds *data_exec, int i)
{
	if (i == 0)
	{
		printf("cmd pipe acion : %s\n", data_exec->cmd);
		ft_first_pipe(data_exec, i);
	}
	else if (i == (data_exec->data.ncmd - 1))
		ft_last_pipe(data_exec, i);
	else
		ft_inter_pipe(data_exec, i);
}

int	init_pipe(t_cmds *data_exec)
{
	int i;

	i = -1;
	data_exec->data.pipe = malloc(sizeof(int *) * data_exec->data.ncmd);
	if (!data_exec->data.pipe)
		return (-1);
	while (++i < data_exec->data.ncmd)
	{
		data_exec->data.pipe[i] = malloc(sizeof(int) * 2);
		if (!data_exec->data.pipe[i])
			return (ft_free_int(data_exec, i), ERROR);
	}
	i = -1;
	while (++i < data_exec->data.ncmd)
	{
		if (pipe(data_exec->data.pipe[i]) == -1)
			return (ft_free_int(data_exec, -1), perror("Error creating pipes"), ERROR);
	}
	return (SUCCESS);
}

int	make_all_exec(t_cmds *data_exec)
{
	pid_t	pid;
	int		i;
	int		pids[1024];

	init_pipe(data_exec);
	i = -1;
	while (++i < data_exec->data.ncmd)
	{
		pid = fork();
		if (pid == -1)
			return (perror("Error process"),
					ft_free_int(data_exec, -1), exit(-1), -1);
		if (pid == 0)
			ft_pipe_action(&data_exec[i], i);
		else
			pids[i] = pid;
	}
	ft_close_all(data_exec);
	i = -1;
	while (++i < data_exec->data.ncmd)
		waitpid(pids[i], NULL, 0);
	ft_free_int(data_exec, -1);
	return (0);
}
