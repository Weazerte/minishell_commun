/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:14:38 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/08 19:47:59 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	nb_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	echo_builtin(int fd, char **args)
{
	int	option;
	int	i;

	option = 0;
	i = 1;
	if (nb_args(args) > 1)
	{
		i = 0;
		while (args[++i])
			if (ft_strncmp(args[i], "-n", 2) == 0)
				option = 1;
		if (option == 1)
			i = 1;
		else
			i = 0;
		while (args[++i])
			ft_putinfd(args[i], fd);
	}
	if (option == 0)
		write(fd, "\n", 1);
}
