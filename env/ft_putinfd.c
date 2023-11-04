/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putinfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:06:21 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/04 21:00:03 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_putinfd(char *content, int fd)
{
	int	i;

	i = -1;
	if (!content)
		return ;
	while (content[++i])
		write(fd, &content[i], 1);
}

void	ft_putinfd_n(char *content, int fd)
{
	int	i;

	i = -1;
	if (!content)
		return ;
	while (content[++i])
		write(fd, &content[i], 1);
	write(fd, "\n", 1);
}
