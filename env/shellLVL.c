/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellLVL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:44:35 by weaz              #+#    #+#             */
/*   Updated: 2023/11/04 20:57:19 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_skip_spacenl(const char *s, int *i)
{
	while (s[(*i)++])
		if (s[(*i)] >= 0 && s[(*i)] <= 9)
			return ;
}

static int	invalid_lvl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	get_lvl(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	ft_skip_spacenl(str, &i);
	if (invalid_lvl(str))
		return (0);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
}

void	increment_shell_level(t_env *lst_env)
{
	int		shell_level;
	char	env_name[BUFF_SIZE];
	char	*shlvl;
	char	*shlvl_value;

	shlvl_value = get_env_value("SHLVL", lst_env);
	if (ft_strcmp(shlvl_value, "") == 0)
		return ;
	shell_level = get_lvl(shlvl_value) + 1;
	ft_memdel(shlvl_value);
	while (lst_env && lst_env->next)
	{
		get_name_in_env(env_name, lst_env->env_line);
		if (ft_strcmp("SHLVL", env_name) == 0)
		{
			ft_memdel(lst_env->env_line);
			shlvl = ft_itoa(shell_level);
			lst_env->env_line = ft_strjoin("SHLVL=", shlvl);
			ft_memdel(shlvl);
			return ;
		}
		lst_env = lst_env->next;
	}
}
