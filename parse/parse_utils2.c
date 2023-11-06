/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:08 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/06 19:03:27 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*free_strs(char *str1, char *str2, char *str3)
{
	if (str1)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
	if (str3)
	{
		free(str3);
		str3 = NULL;
	}
	return (NULL);
}

int	find_nbcmd(char *str)
{
	int	i;
	int	nbcmd;

	i = 0;
	nbcmd = 1;
	while (str[i])
	{
		if (str[i] == '|')
			nbcmd += 1;
		i++;
	}
	return (nbcmd);
}

int	find_next_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (i);
		i++;
	}
	return (-1);
}
char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	i = 0;
	while (s[i] && i < n)
	{
		i++;
	}
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = ft_strlen(dest);
	j = ft_strlen(src);
	k = 0;
	if (size <= i || size == 0)
		return (j + size);
	while (i + k < size - 1 && src[k] != '\0')
	{
		dest[i + k] = src[k];
		k++;
	}
	dest[i + k] = '\0';
	return (i + j);
}