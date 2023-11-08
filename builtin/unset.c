/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:31:47 by weaz              #+#    #+#             */
/*   Updated: 2023/11/08 13:44:36 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	env_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	delete_node(t_env *lst_env, t_env *env)
{
	if (lst_env == env && env->next == NULL)
	{
		ft_memdel(lst_env->env_line);
		lst_env->env_line = NULL;
		lst_env->next = NULL;
		return ;
	}
	ft_memdel(env->env_line);
	ft_memdel(env);
}

void	unset_builtin_comp(char **a, t_env *lst_env, t_env *env, t_env *tmp)
{
	while (env && env->next)
	{
		if (ft_strncmp(a[1], env->next->env_line,
				env_size(env->next->env_line)) == 0)
		{
			tmp = env->next->next;
			delete_node(lst_env, env->next);
			env->next = tmp;
			return ;
		}
		env = env->next;
	}
}

// static void	ft_put_lst(t_env *env)
// {
// 	while (env && env->next)
// 	{
// 		ft_putinfd_n(env->env_line, 1);
// 		env = env->next;
// 	}
// 	if (env->env_line)
// 		ft_putinfd_n(env->env_line, 1);
// }

// lst_env = (env->next) ? env->next : lst_env;
int	unset_builtin(char **a, t_env *lst_env)
{
	t_env	*env;
	t_env	*tmp;

	env = lst_env;
	if (!(a[1]))
		return(SUCCESS);
	if (ft_strncmp(a[1], env->env_line, env_size(env->env_line)) == 0)
	{
		if (env->next)
			lst_env = env->next;
		delete_node(lst_env, env);
		return(SUCCESS);
	}
	tmp = NULL;
	unset_builtin_comp(a, lst_env, env, tmp);
	// ft_put_lst(lst_env);
	return(SUCCESS);
}
