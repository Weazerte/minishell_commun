/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:29:36 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/07 14:56:16 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_error(t_cmds *data, int **pipe)
{
	int	i;

	i = -1;
	if (pipe)
	{
		while (++i < (data->ncmd - 1))
			free(pipe[i]);
		free(pipe);
	}
	i = -1;
	while (++i < data->ncmd)
	{
		if (data[i].cmd)
			ft_memdel(data[i].cmd);
		if (data[i].env)
			free_tab(data[i].env);
	}
}

void	ft_free_cmd(char *str, char **tab)
{
	if (str)
		ft_memdel(str);
	if (tab)
		free_tab(tab);
}

void	ft_close_pipes(t_cmds *data_exec, int **pipe)
{
	int		i;

	i = -1;
	while (++i < (data_exec->ncmd - 1))
		ft_close_fd(pipe[i]);
	i = -1;
	if (pipe)
	{
		while (++i < (data_exec->ncmd - 1))
		{
			if (pipe[i])
				free(pipe[i]);
		}
		free(pipe);
	}
}

void	ft_close_fd(int *fd)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}

int	ft_verif_space(char *str)
{
	int	i;

	i = 0;

	while (str[i])
	{
		if (str[i] == -7)
			return (1);
		i++;
	}
	return (0);
}
