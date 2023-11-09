/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:10:26 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/09 16:37:03 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_len(char **tab, int	i)
{
	int	j;

	j = 0;
	while (tab[i])
	{
		while (tab[i][j])
			j++;
		i++;
	}
	return (j);
}

static void	ft_strnccpy(const char *src, char *dst, int len)
{
	int	i;

	i = 0;
	while (src[i] && i < len)
	{
			dst[i] = src[i];
			i++;
	}
	dst[i] = 0;
}

static void	ft_cpycmd(char **tab, char *dst, int i)
{
	int	j;
	int	k;

	k = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			dst[k] = tab[i][j];
			j++;
			k++;
		}
		if (tab[(i + 1)])
		{
			dst[k] = -7;
			k++;
		}	
		i++;
	}
	dst[k] = 0;
}

void	ft_open_infile(t_cmds *data)
{
	char **tab;
	int	len;
	int	tab_len;
	char *file;

	tab = ft_split(data->cmd, -7);
	len = (int)ft_strlen(tab[1]);
	tab_len = (ft_tab_len(tab) - 2);
	file = malloc(sizeof(char) * (len + tab_len + 1));
	ft_strnccpy(tab[1], file, len);
	data->infile = open(file, O_RDONLY);
	if (data->cmd)
		free(data->cmd);
	len = ft_len(tab, 2);
	data->cmd = malloc(sizeof(char) * (len + 1));
	ft_cpycmd(tab, data->cmd, 2);
	if (file)
		free(file);
	if (tab)
		free_tab(tab);
}
