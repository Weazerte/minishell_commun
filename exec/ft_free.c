/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:49:37 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/09 13:37:17 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tab(char **tab)
{
	int	i;
	
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_free_one_ex(t_cmds *data)
{
	if (data->cmd)
		free(data->cmd);
	free_tab(data->env);
	if (data->infile != 0)
		close(data->infile);
	if (data->outfile != 1)
		close(data->outfile);
}

void	ft_free_mult_ex(t_cmds *data)
{
	int	i;

	i = -1;
	if (data->env)
			free_tab(data->env);
	while (++i < data->ncmd)
	{
		if (data[i].cmd)
			ft_memdel(data[i].cmd);
		if (data[i].infile != 0)
			close(data[i].infile);
		if (data[i].outfile != 1)
			close(data[i].outfile);
	}
}

void ft_free_lst(t_env *lst)
{
	t_env *tmp;
	
	while (lst && lst->next)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->env_line);
		free(tmp);
	}
	if (lst->env_line)
		free(lst->env_line);
	if (lst)
		free(lst);
}
