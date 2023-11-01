/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:04:00 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/01 12:47:36 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	ft_free_list(char **father)
{
	int	i;

	i = 0;
	if (father)
	{
		if (father[i])
		{
			while (father[i])
			{
				free(father[i]);
				i++;
			}
		}
		free(father);
	}
	return ;
}
