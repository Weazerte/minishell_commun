/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_outfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:10:38 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/15 20:21:49 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_len(char *str, char c)
{
	int	i;

	i = 0;
	if (c == 0)
	{
		while (str[i])
			i++;
	}
	else
	{
		while (str[i] && str[i] != c)
			i++;
	}
	return (i);
}

static char	*ft_strjoin_space(char const *s1, char const *s2, char c)
{
	int		i;
	int		j;
	char	*str;

	str = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2)
			* sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	i = -1;
	str[j++] = c;
	while (s2[++i])
	{
		str[j] = s2[i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

static void	ft_open(t_cmds *data, char **tab)
{
	int		i;
	char	*file;

	file = NULL;
	i = 1;
	while (tab[i])
	{
		if (!tab[i + 1])
			break ;
		if (ft_strcmp(tab[i], ">") == 0)
		{
			file = ft_strdup(tab[i + 1]);
			if (data->outfile != 1)
				close(data->outfile);
			if (ft_len(tab[i + 1], 0) == 2)
				data->outfile = open(file, O_CREAT | O_APPEND | O_RDWR, 00644);
			else
				data->outfile = open(file, O_TRUNC | O_CREAT | O_RDWR, 00644);
		}
		if (file)
			free(file);
		file = NULL;
		i++;
	}
}

static char	*open_outfile_tools(char *cmd_cpy, char **tab, int i)
{
	char	*tmp;

	if (i == 1)
		tmp = ft_strjoin_space(cmd_cpy, tab[i], -7);
	else
		tmp = ft_strjoin_space(cmd_cpy, tab[i], ' ');
	ft_memdel(cmd_cpy);
	return (tmp);
}

void	ft_open_outfile(t_cmds *data)
{
	char	**tab;
	char	*cmd_cpy;
	int		i;

	tab = ft_split(data->cmd, -7);
	ft_open(data, tab);
	cmd_cpy = ft_strdup(tab[0]);
	i = 0;
	while (tab[++i])
	{
		if (ft_strcmp(tab[i], ">") != 0)
			cmd_cpy = open_outfile_tools(cmd_cpy, tab, i);
		else
			i++;
	}
	free_tab(tab);
	data->cmd = ft_strdup(cmd_cpy);
	ft_memdel(cmd_cpy);
}
