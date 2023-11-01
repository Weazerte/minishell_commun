/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putinfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:06:21 by eaubry            #+#    #+#             */
/*   Updated: 2023/10/31 13:41:33 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_putinfd(char *content, int fd)
{
	int	i;

	i = 0;
	if (!content)
		return ;
	while (content[i++])
		write(fd, &content[i], 1);
}

void	ft_putinfd_n(char *content, int fd)
{
	int	i;

	i = 0;
	if (!content)
		return ;
	while (content[i++])
		write(fd, &content[i], 1);
	write(fd, "\n", 1);
}