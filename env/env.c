/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:25:32 by weaz              #+#    #+#             */
/*   Updated: 2023/11/01 11:42:02 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t			size_env(t_env *lst_env)
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

char			*env_to_str(t_env *lst_env)
{
	char	*env;
	int		i;
	int		j;

	if (!(env = malloc(sizeof(char) * size_env(lst_env) + 1)))
		return (NULL);
	i = 0;
	while (lst_env && lst_env->next != NULL)
	{
		if (lst_env->env_line != NULL)
		{
			j = 0;
			while (lst_env->env_line[j])
			{
				env[i] = lst_env->env_line[j];
				i++;
				j++;
			}
		}
		if (lst_env->next->next != NULL)
			env[i++] = '\n';
		lst_env = lst_env->next;
	}
	env[i] = '\0';
	return (env);
}

int				env_init(t_env **lst_env, char **env)
{
	t_env	*new;
	t_env	*start;
	int		i;

	*lst_env = malloc(sizeof(t_env));
	if (!(*lst_env))
		return (1);
	start = (*lst_env);
	(*lst_env)->env_line = ft_strdup(env[0]);
	(*lst_env)->next = NULL;
	i = 1;
	while (env && env[i])
	{
		if (!(new = malloc(sizeof(t_env))))
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

int				secret_env_init(t_env *lst_secret, char **env)
{
	t_env	*new;
	int		i;

	if (!(lst_secret = malloc(sizeof(t_env))))
		return (1);
	lst_secret->env_line = ft_strdup(env[0]);
	lst_secret->next = NULL;
	i = 1;
	while (env && env[0] && env[i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (1);
		new->env_line = ft_strdup(env[i]);
		new->next = NULL;
		lst_secret->next = new;
		lst_secret = new;
		i++;
	}
	return (0);
}