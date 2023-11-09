/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_outfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:10:38 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/09 16:32:50 by eaubry           ###   ########.fr       */
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

static void	ft_strnccpy(const char *src, char *dst, int len, char c)
{
	int	i;
	int	j;

	i = 0;
	if (c != 0)
	{
		while (src[i] && src[i] != c)
			i++;
		i += 2;
	}
	j = 0;
	while (src[i] && j < len)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = 0;
}

static void	ft_cpycmd(const char *src, char *dst, int len)
{
	int	i;

	i = 0;
	while (src[i] && i < len)
	{
		if (src[i] == ' ')
			dst[i] = -7;
		else
			dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

void	ft_free_for_open(char *s1, char *s2, char **tab)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (tab)
		free_tab(tab);
}

void	ft_open_outfile(t_cmds *data)
{
	char	**tab;
	int		len;
	int		len_tab;
	char	*file;
	char	*cmd_cpy;

	tab = ft_split(data->cmd, -7);
	len_tab = (ft_tab_len(tab) - 1);
	len = 0;
	while (tab[len_tab][len])
		len++;
	file = malloc(sizeof(char) * (len + 1));
	ft_strnccpy(tab[len_tab], file, ft_len(tab[len_tab], 0), 0);
	if (ft_len(tab[len_tab - 1], 0) == 2)
		data->outfile = open(file, O_CREAT | O_APPEND | O_RDWR, 00644);
	else
		data->outfile = open(file, O_TRUNC | O_CREAT | O_RDWR, 00644);
	cmd_cpy = ft_strdup(data->cmd);
	if (data->cmd)
		free(data->cmd);
	len = (ft_len(cmd_cpy, '>') - 1);
	data->cmd = malloc(sizeof(char) * (len + 1));
	ft_cpycmd(cmd_cpy, data->cmd, len);
	ft_free_for_open(file, cmd_cpy, tab);
}
