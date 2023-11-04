/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:09:27 by weaz              #+#    #+#             */
/*   Updated: 2023/11/04 20:38:58 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_builtin(t_env *lst_env, int fd)
{
	while (lst_env->next)
	{
		ft_putinfd_n(lst_env->env_line, fd);
		lst_env = lst_env->next;
	}
	if (lst_env)
		ft_putinfd_n(lst_env->env_line, fd);
	return (0);
}
