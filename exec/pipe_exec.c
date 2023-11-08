/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:16:30 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/08 23:33:10 by eaubry           ###   ########.fr       */
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

void	ft_first_pipe(t_cmds *data_exec, int **pip, t_env *lst_env)
{
	int	j;

	j = 0;
	close(pip[0][0]);
	while (++j < (data_exec->ncmd - 1))
		ft_close_fd(pip[j]);
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_multexec_args(data_exec, data_exec->infile, pip[0][1], lst_env);
	else
		ft_multexec_noargs(data_exec, data_exec->infile, pip[0][1], lst_env);
}

void	ft_inter_pipe(t_cmds *data_exec, int **pip, int i, t_env *lst_env)
{
	int	j;
	
	close(pip[i][0]);
	close(pip[i - 1][1]);
	j = -1;
	while (++j < (data_exec->ncmd - 1))
		if (j != i && j != (i - 1))
			ft_close_fd(pip[j]);
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_multexec_args(data_exec, pip[i - 1][0], pip[i][1], lst_env);
	else
		ft_multexec_noargs(data_exec, pip[i - 1][0], pip[i][1], lst_env);
}

void	ft_last_pipe(t_cmds *data_exec, int **pip, int i, t_env *lst_env)
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
			ft_multexec_args(data_exec, data_exec->infile, data_exec->outfile, lst_env);
		else
			ft_multexec_noargs(data_exec, data_exec->infile, data_exec->outfile, lst_env);
	}
	
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_multexec_args(data_exec, pip[i - 1][0], data_exec->outfile, lst_env);
	else
		ft_multexec_noargs(data_exec, pip[i - 1][0], data_exec->outfile, lst_env);
}

void	pipe_redirect(t_cmds *data_exec, int **pipe, int i, t_env *lst_env)
{
	// printf("%d\n", data_exec->ncmd);
	if (i == 0)
		ft_first_pipe(data_exec, pipe, lst_env);
	else if (i == (data_exec->ncmd - 1))
		ft_last_pipe(data_exec, pipe, i, lst_env);
	else
		ft_inter_pipe(data_exec, pipe, i, lst_env);
}
