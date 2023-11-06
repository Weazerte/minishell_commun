/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:49:37 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/06 22:09:47 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tab(char **tab)
{
	int	i;
	
	i = -1;
	while (tab[++i])
		if (tab[i])
			ft_memdel(tab[i]);
	if (tab)
		ft_memdel(tab);
}

void	ft_free_one_ex(t_cmds *data)
{
	if (data->cmd)
		ft_memdel(data->cmd);
	if (data->env)
		free_tab(data->env);
	if (data->infile != 0)
		close(data->infile);
	if (data->outfile != 0)
		close(data->outfile);
	// if (data->lst_env)
	// 	ft_free_lst(data->lst_env);
	// if (data)
	// 	ft_memdel(data);
}

void	ft_free_mult_ex(t_cmds *data)
{
	int	i;

	i = -1;
	while (++i < data->ncmd)
	{
		if (data[i].cmd)
			ft_memdel(data[i].cmd);
		if (data[i].env)
			free_tab(data[i].env);
		// if (data[i].infile != 0)
		// 	close(data[i].infile);
		// if (data[i].outfile != 0)
		// 	close(data[i].outfile);
		// if (data[i].lst_env)
		// 	ft_free_lst(data[i].lst_env);
	}
}

void ft_free_lst(t_env *lst)
{
	t_env *tmp;
	while (lst && lst->next)
	{
		tmp = lst->next;
		if (lst->env_line)
			free(lst->env_line);
		if (lst)
			free(lst);
		lst = tmp;
	}
	if (lst->env_line)
		free(lst->env_line);
	if (lst)
		free(lst);
}