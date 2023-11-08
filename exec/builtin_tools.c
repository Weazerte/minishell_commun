/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:34:47 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/08 19:18:33 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_a_not_forked_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] == -7)
		return (0);
	if (ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] == -7)
		return (0);
	if (ft_strncmp(cmd, "unset", 5) == 0 && cmd[5] == -7)
		return (0);
	if (ft_strncmp(cmd, "export", 6) == 0 && cmd[6] == -7)
		return (0);
	return (1);
}

int	is_a_forked_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (0);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (0);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (0);
	return (1);
}

void	ft_put_unknow_cmd(char *cmd)
{
	ft_putinfd("minishell:", STDERR);
	ft_putinfd(cmd, STDERR);
	ft_putinfd_n(": command not found", STDERR);
}
