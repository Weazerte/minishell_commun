/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:16:30 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/04 20:20:47 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_pipe(t_cmds *data_exec, int ***pip)
{
	int	j;

	j = -1;
	*pip = malloc(sizeof(int *) * (data_exec->ncmd - 1));
	if (!(*pip))
		return (-1);
	while (++j < (data_exec->ncmd -1))
	{
		(*pip)[j] = malloc(sizeof(int) * 2);
		if (!(*pip)[j])
			return (ERROR);
	}
	j = -1;
	while (++j < (data_exec->ncmd - 1))
	{
		if (pipe((*pip)[j]) == -1)
			return (ERROR);
	}
	return (SUCCESS);
}

void	ft_first_pipe(t_cmds *data_exec, int **pip)
{
	int	j;

	j = 0;
	close(pip[0][0]);
	while (++j < (data_exec->ncmd - 1))
		ft_close_fd(pip[j]);
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_multexec_args(data_exec, data_exec->infile, pip[0][1]);
	else
		ft_multexec_noargs(data_exec, data_exec->infile, pip[0][1]);
}

void	ft_inter_pipe(t_cmds *data_exec, int **pip, int i)
{
	int	j;

	//close les pipes pas utilises
	if (data_exec->infile != -1 && data_exec->infile != 1)
		close(data_exec->infile);
	if (data_exec->outfile != -1 && data_exec->outfile != 0)
    	close(data_exec->outfile);
	close(pip[i][0]);
	close(pip[i - 1][1]);
	j = -1;
	while (++j < (data_exec->ncmd - 1))
		if (j != i && j != (i - 1))
			ft_close_fd(pip[j]);
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_multexec_args(data_exec, pip[i - 1][0], pip[i][1]);
	else
		ft_multexec_noargs(data_exec, pip[i - 1][0], pip[i][1]);
}

void	ft_last_pipe(t_cmds *data_exec, int **pip, int i)
{
	int	j;

	close(pip[(i - 1)][1]);
	j = -1;
	while (++j < (i - 1))
		ft_close_fd(pip[j]);
	if (data_exec->infile != 0)
	{
		close(pip[i - 1][0]);
		if ((ft_verif_space(data_exec->cmd) == 1))
			ft_multexec_args(data_exec, data_exec->infile, data_exec->outfile);
		else
			ft_multexec_noargs(data_exec, data_exec->infile, data_exec->outfile);
	}
	
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_multexec_args(data_exec, pip[i - 1][0], data_exec->outfile);
	else
		ft_multexec_noargs(data_exec, pip[i - 1][0], data_exec->outfile);
}

void	ft_pipe_action(t_cmds *data_exec, int **pipe, int i)
{
	if (i == 0)
		ft_first_pipe(data_exec, pipe);
	else if (i == (data_exec->ncmd - 1))
		ft_last_pipe(data_exec, pipe, i);
	else
		ft_inter_pipe(data_exec, pipe, i);
}
