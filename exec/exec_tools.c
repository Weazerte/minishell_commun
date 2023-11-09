/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:24:33 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/09 13:08:56 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


char	*ft_find_bin(char **tab)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	while (tab[i])
	{
		if (access(tab[i], F_OK | X_OK) == 0)
		{
			str = ft_strdup(tab[i]);
			return (str);
		}
		i++;
	}
	return (NULL);
}

char	*ft_cut_path(char *path)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		path++;
		i++;
	}
	return (path);
}

char	*ft_path(t_env *lst_env)
{
	while (lst_env->next)
	{
		if (ft_strncmp(lst_env->env_line, "PATH=", 5) == 0)
			return (lst_env->env_line);
		lst_env = lst_env->next;
	}
	return (NULL);
}

char	**ft_join_tab_cmd(char **tab, char *cmd)
{
	int	i;
	char **tab2;
	int	len;

	len = 0;
	while (tab[len])
		len++;
	tab2 = malloc(sizeof(char *) * (len + 1));
	if (!tab2)
		return (free_tab(tab), NULL);
	i = -1;
	while (tab[++i])
		tab2[i] = ft_join_path(tab[i], cmd); // fonction dans builtin_tools
	tab2[i] = NULL;
	free_tab(tab);
	return (tab2);
}

char	*ft_path_bin(char *cmd, t_env *lst_env)
{
	char	**tab;
	char	*path;

	path = NULL;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_path(lst_env);
	if (path == NULL)
		return (NULL);
	path = ft_cut_path(path);
	tab = ft_split(path, ':');
	tab = ft_join_tab_cmd(tab, cmd);
	if (tab == NULL)
		return (NULL);
	path = ft_find_bin(tab);
	free_tab(tab);
	if (path == NULL)
		return (NULL);
	return (path);
}
