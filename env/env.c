/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:25:32 by weaz              #+#    #+#             */
/*   Updated: 2023/11/08 20:11:25 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**env_to_tab(t_env *lst_env)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_env_lstsize(lst_env) + 1));
	while (lst_env)
	{
		tab[i] = ft_strdup(lst_env->env_line);
		i++;
		lst_env = lst_env->next;
	}
	tab[i] = NULL;
	return (tab);
}

size_t	size_env(t_env *lst_env)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst_env && lst_env->next != NULL)
	{
		if (lst_env->env_line != NULL)
		{
			lst_len += ft_strlen(lst_env->env_line);
			lst_len++;
		}
		lst_env = lst_env->next;
	}
	return (lst_len);
}

char	*env_to_str(t_env *lst_env)
{
	char	*env;
	int		i;
	int		j;

	env = malloc(sizeof(char) * size_env(lst_env) + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (lst_env && lst_env->next != NULL)
	{
		if (lst_env->env_line != NULL)
		{
			j = -1;
			while (lst_env->env_line[++j])
			{
				env[i] = lst_env->env_line[j];
				i++;
			}
		}
		if (lst_env->next->next != NULL)
			env[i++] = '\n';
		lst_env = lst_env->next;
	}
	env[i] = '\0';
	return (env);
}

int	env_init(t_env **lst_env, char **env)
{
	t_env	*new;
	t_env	*start;
	int		i;

	*lst_env = malloc(sizeof(t_env));
	if (!(*lst_env))
		return (1);
	(*lst_env)->env_line = ft_strdup(env[0]);
	(*lst_env)->next = NULL;
	start = (*lst_env);
	i = 1;
	while (env && env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->env_line = ft_strdup(env[i]);
		new->next = NULL;
		(*lst_env)->next = new;
		(*lst_env) = new;
		i++;
	}
	(*lst_env) = start;
	return (0);
}
