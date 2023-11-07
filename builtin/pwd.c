/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:28:33 by weaz              #+#    #+#             */
/*   Updated: 2023/11/07 13:46:21 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pwd_builitn(int fd)
{
	char	cwd[300];

	if (getcwd(cwd, 300))
	{
		ft_putendl_fd(cwd, fd);
		exit(SUCCESS);
	}
	else
		exit(ERROR);
}
