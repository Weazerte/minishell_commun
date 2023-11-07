/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:34:47 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/07 17:39:20 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_put_unknow_cmd(char *cmd)
{
	ft_putinfd("minishell:", STDERR);
	ft_putinfd(cmd, STDERR);
	ft_putinfd_n(": command not found", STDERR);
}
