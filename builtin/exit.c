/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:09:47 by weaz              #+#    #+#             */
/*   Updated: 2023/11/07 14:04:17 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exit_builtin(char **cmd)
{
	ft_putinfd_n("exit", STDERR);
	if ((cmd[1] && cmd[2]) && ft_strisnum(cmd[1]) == 0)
	{
		ft_putinfd("minishell: exit: ", STDERR);
		ft_putinfd(cmd[1], STDERR);
		ft_putinfd_n(": numeric argument required", STDERR);
		exit(255);
	}
	else if (cmd[1] && cmd[2])
	{
		ft_putinfd_n("minishell: exit: too many arguments", STDERR);
		exit(1);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		ft_putinfd("minishell: exit: ", STDERR);
		ft_putinfd(cmd[1], STDERR);
		ft_putinfd_n(": numeric argument required", STDERR);
		exit(255);
	}
	else if (cmd[1])
		exit(ft_atoi(cmd[1]));
	else
		exit(SUCCESS);
}
